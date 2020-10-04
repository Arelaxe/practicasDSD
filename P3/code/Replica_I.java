import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Replica_I extends Remote {
  public int getNumberOfDonations () throws RemoteException;
}
