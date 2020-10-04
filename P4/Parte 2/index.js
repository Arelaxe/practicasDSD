var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");

var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", 
    "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript",
    "css": "text/css", "swf": "application/x-shockwave-flash"};

var httpServer = http.createServer(
    function(request, response) {
        var uri = url.parse(request.url).pathname;
        if (uri=="/") uri = "/vista_usuario.html";
        else if (uri.includes('sensores')) uri = "/sensores.html";
        console.log(uri);
        var fname = path.join(process.cwd(), uri);
        fs.exists(fname, function(exists){
            if (exists) {
                fs.readFile(fname, function(err, data) {
                    if (!err) {
                        var extension = path.extname(fname).split(".")[1];
                        var mimeType = mimeTypes[extension];
                        response.writeHead(200, mimeType);
                        response.write(data);
                        response.end();
                    }
                    else {
                        response.writeHead(200, {"Content-Type": "text/plain"});
                        response.write('Error de lectura en el fichero: '+uri);
                        response.end();
                    }
                });
            }
            else{
                console.log("Peticion invalida"+uri);
                response.writeHead(200, {"Content-Type": "text/plain"});
                response.write('404 Not Found\n');
                response.end();
            }
        });
    }
);
httpServer.listen(8081);
var io = socketio.listen(httpServer);

var allClients = new Array();
io.sockets.on('connection', function(client) {
    allClients.push({address:client.request.connection.remoteAddress, port:client.request.connection.remotePort});
    console.log('New connection from ' + client.request.connection.remoteAddress + ':' + client.request.connection.remotePort);
    io.sockets.emit('all-connections', allClients);
    client.on('output-evt', function (data) {
        client.emit('output-evt', 'Hola Cliente!');
    });
    client.on('disconnect', function() {
        console.log("El cliente "+client.request.connection.remoteAddress+" se va a desconectar");
        console.log(allClients);

        var index = -1;
        for (var i = 0; i<allClients.length; i++){
            //console.log("Hay "+allClients[i].port);
            if(allClients[i].address == client.request.connection.remoteAddress 
                && allClients[i].port == client.request.connection.remotePort){
                    index = i;
                }
        }

        if (index != -1) {
            allClients.splice(index, 1);
            io.sockets.emit('all-connections', allClients);
        } else{
            console.log("EL USUARIO NO SE HA ENCONTRADO!")
        }
        console.log('El usuario '+client.request.connection.remoteAddress+' se ha desconectado');
    });
});

console.log("Servicio Socket.io iniciado");

var datos = new Array(100).fill(0);

MongoClient.connect("mongodb://localhost:27017/", function(err, db){
    var dbo = db.db("servidorIOT");
    dbo.createCollection("historico_sensores", function(err, collection){
        io.sockets.on('connection', 
        function(client){
            client.emit('inicializar', collection.find({}).toArray(function(err, results){
                client.emit('obtener',results);
            }));
            client.on('borrar', function(data){
                collection.remove({});
            });
            client.on('add_cambio', function (data) {
                io.sockets.emit('update_cambios', {variable:data.variable, value:data.value, host:client.request.connection.remoteAddress, port:client.request.connection.remotePort, date:data.date});
            });
            client.on('poner', function(data){
                collection.insert(data, {safe:true}, function(err, result) {});
            });
            client.on('obtener', function() {
                collection.find({}).toArray(function(err, results){
                    client.emit('obten', results);
                });
            });
            client.on('apagar_persiana', function(){
                var d = new Date();
                var data = {};
                data.variable = "Persiana";
                data.value = "OFF";
                data.host = "Agente";
                data.port = "Agente";
                data.date = d;
                io.sockets.emit('update_cambios', {variable:data.variable, value:data.value, host:data.host, port:data.port, date:data.date});
            });
        });
    });
    dbo.createCollection("valor_ac", function(err, collection){
        io.sockets.on('connection',
        function(client){
            client.emit('inicializar_ac', collection.find({}).toArray(function(err, results) {
                client.emit('init_ac', results);
            }));
            client.on('add_nueva_ac', function(data){
                io.sockets.emit('update_ac', {ac: data.ac});
                collection.insert(data, {safe:true}, function(err, result) {});
            });
            client.on('borrar', function(data){
                collection.remove({});
                collection.insert({ac: data.ac}, {safe:true}, function(err, result){});
            });
        });
    });
    dbo.createCollection("valor_persiana", function(err, collection){
        io.sockets.on('connection',
        function(client){
            client.emit('inicializar_persiana', collection.find({}).toArray(function(err, results){
                client.emit('init_persiana', results);
            }));
            client.on('add_nueva_persiana', function(data){
                io.sockets.emit('update_persiana', {persiana: data.persiana});
                collection.insert(data, {safe:true}, function(err, result) {});
            });
            client.on('borrar', function(data){
                collection.remove({});
                collection.insert({persiana: data.persiana}, {safe:true}, function(err, result){});
            });
            client.on('apagar_persiana', function(data){
                io.sockets.emit('persiana_off', data);
                collection.insert(data, {safe:true}, function(err, result) {});
            });
        });
    });
    dbo.createCollection("valor_temperatura", function(err, collection){
        io.sockets.on('connection',
        function(client){
            client.emit('inicializar_temperatura', collection.find({}).toArray(function(err, results){
                client.emit('init_temperatura', results);
            }));
            client.on('add_nueva_temperatura', function(data){
                io.sockets.emit('update_temperatura', {temperatura: data.temperatura});
                collection.insert(data, {safe:true}, function(err, result) {});
            });
            client.on('borrar', function(data){
                collection.remove({});
                collection.insert({temperatura: data.temperatura}, {safe:true}, function(err, result){});
            });
        });
    });
    dbo.createCollection("valor_luminosidad", function(err, collection){
        io.sockets.on('connection',
        function(client){
            client.emit('inicializar_luminosidad', collection.find({}).toArray(function(err, results){
                client.emit('init_luminosidad', results);
            }));
            client.on('add_nueva_luminosidad', function(data){
                io.sockets.emit('update_luminosidad', {luminosidad: data.luminosidad});
                collection.insert(data, {safe:true}, function(err, result) {}); 
            });
            client.on('borrar', function(data){
                collection.remove({});
                collection.insert({luminosidad: data.luminosidad}, {safe:true}, function(err, result){});
            });
        });
    });
});

console.log("Servivio MongoDB iniciado");