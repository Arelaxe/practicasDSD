import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Cliente {
    public static void main(String args[]) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            Scanner s = new Scanner(System.in);
            String nombre_us = "";
            String pass_us = "";
            String opcion = "";
            Boolean existe = false;
            Boolean credenciales = false;
            String server = "";
            Replica_I serverUsuario;

            String remoteObjectName = "Replica1";

            System.out.println("Searching remote object");
            Registry registry = LocateRegistry.getRegistry("localhost");
            Replica_I localObject = (Replica_I) registry.lookup(remoteObjectName); // Buscamos la réplica 1
            
            do{
                System.out.println("1: Registrarse\n2: Iniciar sesión\n");
                opcion = s.next();
                s.nextLine();
            } while (!opcion.equals("1") && !opcion.equals("2")); // Mientas la opción elegida no esté disponible
            
            if (opcion.equals("1")){ // Registro
                do{
                    System.out.print("Elige un nombre de usuario: "); // Pedimos un nombre de usuario
                    nombre_us = s.next();
                    s.nextLine();
                    existe = localObject.existeUsuario(nombre_us); // Comprobamos que el usuario no exista
                }while (existe);

                System.out.print("Elige una contraseña: "); // Pedimos la contraseña
                pass_us = s.next();
                s.nextLine();
                localObject.registrarUsuario(nombre_us,pass_us);
            }
            else if (opcion.equals("2")){ // Inicio de sesión
                do{
                    System.out.print("Introduce nombre de usuario: "); // Pedimos el nombre de usuario
                    nombre_us = s.next();
                    s.nextLine();
                    System.out.print("Introduce tu contraseña: "); // Pedimos la contraseña 
                    pass_us = s.next();
                    s.nextLine();
                    credenciales = localObject.credencialesCorrectos(nombre_us,pass_us); // Comprobamos que estos
                }while (!credenciales);                                                  // credenciales son  correctos
            }
            
            server = localObject.getServerUsuario(nombre_us); // Comprobamos en qué réplica está registrado el usuario
            if (server.equals("2")){ // Conectamos con una réplica u otra, dependiendo de cuál sea
                serverUsuario = (Replica_I) registry.lookup("Replica2");
            }
            else{
                serverUsuario = (Replica_I) registry.lookup("Replica1");
            }
              
            do{
                System.out.println("1: Donar\n2: Consultar donaciones\n3: Salir"); // Preguntamos la acción a realizar
                opcion = s.next();
                s.nextLine();
                if (opcion.equals("1")){ // Donar
                    System.out.print("Elige la cantidad a donar: ");
                    String dinero = s.next();
                    s.nextLine();
                    serverUsuario.aniadeDonacion(Float.parseFloat(dinero),nombre_us);
                }
                if (opcion.equals("2")){ // Consultar donaciones
                    float valor = serverUsuario.getTotalDonado(nombre_us);
                    if (valor == -1){ // getTotalDonado devuelve -1 si el usuario aún no ha hecho ninguna donación
                        System.out.println("Tienes que haber realizado una donación para realizar esta acción\n");
                    }
                    else{
                        System.out.println("Hay "+valor+" euros donados\n");
                    }
                }
            } while (opcion.equals("1") || opcion.equals("2") || !opcion.equals("3")); // hasta que la opción sea salir
            
            s.close(); // Cerramos el escáner
        } catch (Exception e) {
            System.err.println("Client exception:");
            e.printStackTrace();
        }
    }
}