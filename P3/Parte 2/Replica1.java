import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;
import java.util.*;
import java.rmi.server.UnicastRemoteObject;

public class Replica1 implements Replica_I{
    private int donaciones = 0;
    private float dinero = 0;
    private ArrayList<Usuario> usuarios = new ArrayList<>();
    private ArrayList<String> nombres_usuario = new ArrayList<>();

    public Replica1() {
        super();
    }

    public float getDinero(){
        return dinero; // Devolvemos el dinero donado en esta réplica
    }

    public Boolean credencialesCorrectos (String nombre, String pass){
        Boolean correctos = false;
        int indice = 0;
        try{
            if (existeUsuario (nombre)){ // Comprobamos que existe el usuario en alguna de las réplicas
                if (nombres_usuario.size()>0){ // Nos aseguramos de que tenemos algún usuario en esta réplica
                    if (nombres_usuario.contains(nombre)){ // Si tenemos ese usuario registrado
                        indice = nombres_usuario.indexOf(nombre);
                        if (usuarios.get(indice).getPass().equals(pass)) // Miramos si la contraseña coincide
                            correctos = true;
                    }
                    else { // Si no lo tenemos registrado, buscamos en la otra réplica
                        Replica_I localObject = buscarReplica(); // Buscamos la réplica
                        if (localObject!=null){ // Si existe
                            correctos = localObject.credencialesCorrectos(nombre,pass); // Miramos en la otra réplica
                        }   
                    } 
                }
                else { // Si no tenemos usuarios en esta réplica miramos en la otra
                    Replica_I localObject = buscarReplica();
                    if (localObject!=null){
                        correctos = localObject.credencialesCorrectos(nombre,pass);
                    }   
                }
            }
        } catch (Exception e){
            System.err.println("credencialesCorrectos exception:");
            e.printStackTrace();
        }   

        return correctos;
    }

    public void registrarUsuario(String nombre, String pass){
        Replica_I localObject = buscarReplica(); // Buscamos la réplica
        ArrayList<String> usu_rep2 = new ArrayList<>();
        Usuario user = new Usuario (); // Creamos un usuario con el nombre y
        user.setNombre(nombre);        // la contraseña que nos han pasado
        user.setPass(pass);

        try{
            if (localObject != null){ // Si la réplica existe
                usu_rep2 = localObject.getNombresUsuario(); // Buscamos los nombres de usuario de la otra réplica
                if (usu_rep2.size()>nombres_usuario.size()){ // Si esta réplica tiene menos usuarios
                    usuarios.add(user); // Añadimos el usuario
                    nombres_usuario.add(nombre); // Añadimos también su nombre a la lista
                    System.out.println("Registro contabilizado en esta réplica"); // Informamos del registro
                }
                else{ // Si esta réplica no tiene menos usuarios
                    localObject.registrarUsuario(nombre,pass); // Lo registramos en la otra
                }
            }
            else{ // Si la otra réplica no existe registramos al usuario en esta
                usuarios.add(user); 
                nombres_usuario.add(nombre); 
                System.out.println("Registro contabilizado en esta réplica"); 
            }
        } catch (Exception e){
            System.err.println("RegistrarUsuario exception:");
            e.printStackTrace();
        }
    }
    public Boolean existeUsuario(String nombre){
        Boolean existe = false;
        try{
            if (nombres_usuario.size()>0){ // Comprobamos si hay algún usuario registrado en esta réplica
                if (nombres_usuario.contains(nombre)) // Comprobamos si la lista de nombres contiene al usuario
                    existe = true;
                else{
                    Replica_I localObject = buscarReplica(); // Buscamos la réplica
                    ArrayList<String> usu_rep2 = new ArrayList<>();
                    if (localObject!=null){ // Si la réplica existe
                        usu_rep2 = localObject.getNombresUsuario(); // Cogemos la lista de nombres de usuario de la réplica
                        if (usu_rep2.contains(nombre)){ // Comprobamos si la réplica contine ese nombre de usuario
                            existe = true;
                        }
                    }   
                }
            }
            else{ // Si no, buscamos en la réplica
                Replica_I localObject = buscarReplica();
                ArrayList<String> usu_rep2 = new ArrayList<>();
                if (localObject!=null){
                    usu_rep2 = localObject.getNombresUsuario();
                    if (usu_rep2.contains(nombre)){
                        existe = true;
                    }
                } 
            }
        } catch (Exception e){
            System.err.println("existeUsuario exception:");
            e.printStackTrace();
        }   

        return existe;
    }

    public void aniadeDonacion(float valor, String usuario){
        try{
            Replica_I localObject = buscarReplica(); // Buscamos la otra réplica
            Usuario user = new Usuario(); 
            int indice = nombres_usuario.indexOf(usuario); // Buscamos el usuario 
            user = usuarios.get(indice);               // que nos ha donado
            user.setDonacion(); // Informamos de que el usuario ha hecho una donacion
        } catch (Exception e){
            System.err.println("aniadeDonacion exception:");
            e.printStackTrace();
        }
        dinero += valor; // Sumamos el dinero de la donación a la réplica
        donaciones++; // Contabilizamos otradonación en la réplica
        System.out.println("He recibido una donación de "+valor+" euros");
        System.out.println("Me han hecho "+donaciones+" donaciones");
        System.out.println("Tengo "+dinero+" euros");
    }

    public Replica_I buscarReplica(){
        Registry registry;
        Replica_I localObject = null;
        try{
            registry = LocateRegistry.getRegistry("localhost");
            localObject = (Replica_I) registry.lookup("Replica2");
        } catch (Exception e){
            System.err.println("buscarReplica exception:");
            e.printStackTrace();
        }  

        if (localObject!=null){
            return localObject;
        }
        else
            return null;
    }

    public ArrayList<Usuario> getUsuarios (){
        return usuarios;
    }

    public ArrayList<String> getNombresUsuario(){
        return nombres_usuario;
    }

    public String getServerUsuario(String nombre){
        String server = "";
        try{
            if (nombres_usuario.size()>0){ // Nos aseguramos de que tenemos algún usuario registrado
                if (nombres_usuario.contains(nombre)) // Comprobamos si tenemos ese usuario en esta réplica
                    server = "1";
                else{ // Si no lo tenemos en esta réplica
                    Replica_I localObject = buscarReplica(); // Buscamos la otra réplica 
                    ArrayList<String> usu_rep2 = new ArrayList<>();
                    if (localObject!=null){ // Comprobamos que existe
                        usu_rep2 = localObject.getNombresUsuario(); // Pedimos los nombres de los usuarios de la otra réplica
                        if (usu_rep2.contains(nombre)){ // Comprobamos que está en la otra réplica
                            server = "2";
                        }
                    }   
                }
            }
            else{ // Si no tenemos ningún usuario registrado aquí, miramos en la otra réplica
                Replica_I localObject = buscarReplica();
                ArrayList<String> usu_rep2 = new ArrayList<>();
                if (localObject!=null){
                    usu_rep2 = localObject.getNombresUsuario();
                    if (usu_rep2.contains(nombre)){
                        server = "2";
                    }
                } 
            }
        } catch (Exception e){
            System.err.println("existeUsuario exception:");
            e.printStackTrace();
        }   

        return server;
    }

    public float getTotalDonado(String usuario){
        float total = 0;
        try{
            Usuario user = new Usuario();
            int indice = nombres_usuario.indexOf(usuario); // Buscamos al usuario que ha donado, sabemos que existe,
            user = usuarios.get(indice);                   // ya que al llegar a este punto se ha debido de identificar
            if(user.getDonacion()){ // Comprobamos si ese usuario ya ha donado
                Replica_I localObject = buscarReplica(); // Buscamos la otra réplica
                total = localObject.getDinero() + dinero; // Sumamos el dinero de esta réplica y de la otra
            }
            else{ // Si no ha realizado ninguna donación, no puede ver el total donado
                total = -1;
            }
        } catch (Exception e){
            System.err.println("getTotalDonado exception:");
            e.printStackTrace();
        } 
        
        return total;
    }

    public static void main(String[] args) {
        // Crea e instala el gestor de seguridad
        if(System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try{
            String remoteObjectName = "Replica1";
            Replica_I object = new Replica1();
            Replica_I stub = (Replica_I) UnicastRemoteObject.exportObject(object, 0);
            Registry registry = LocateRegistry.getRegistry("localhost");
            registry.rebind(remoteObjectName, stub);
            System.out.println("Replica 1 lista");
        } catch (Exception e) {
            System.err.println("Replica 1 exception:");
            e.printStackTrace();
        }
    }
}