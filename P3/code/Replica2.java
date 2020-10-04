import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Replica2 implements Replica_I
{
    public static void main(String[] args)
    {
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }

        try {
            String remoteObjectName = "Replica2";
            Replica_I object = new Replica2();
            Replica_I stub = (Replica_I) UnicastRemoteObject.exportObject(object, 0);
            Registry registry = LocateRegistry.getRegistry();
            registry.rebind(remoteObjectName, stub);
            System.out.println("Replica 2 ready");
        } catch (Exception e) {
            System.err.println("Replica 2 exception:");
            e.printStackTrace();
        }
    }

    public int getNumberOfDonations()
    {
        return 128;
    }
}
