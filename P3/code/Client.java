import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Client {
    public static void main(String args[]) {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            String remoteObjectName = "";
            Scanner s = new Scanner(System.in);
            System.out.println("With what replica do you want to communicate (\"Replica1\" or \"Replica2\")?");
            if (s.hasNext()) {
                remoteObjectName = s.next();
                s.nextLine();
            }
            s.close();
            System.out.println(remoteObjectName);

            System.out.println("Searching remote object");
            Registry registry = LocateRegistry.getRegistry("localhost");
            Replica_I localObject = (Replica_I) registry.lookup(remoteObjectName);
            System.out.print("Number of donations: ");
            System.out.println(localObject.getNumberOfDonations());
        } catch (Exception e) {
            System.err.println("Client exception:");
            e.printStackTrace();
        }
    }
}
