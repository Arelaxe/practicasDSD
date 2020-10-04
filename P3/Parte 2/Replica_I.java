import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.*;

public interface Replica_I extends Remote {
    public float getDinero () throws RemoteException;
    public void registrarUsuario (String nombre, String pass) throws RemoteException;
    public void aniadeDonacion (float valor, String usuario) throws RemoteException;
    public Replica_I buscarReplica() throws RemoteException;
    public ArrayList<Usuario> getUsuarios () throws RemoteException;
    public ArrayList<String> getNombresUsuario () throws RemoteException;
    public Boolean existeUsuario (String nombre) throws RemoteException;
    public Boolean credencialesCorrectos (String nombre, String pass) throws RemoteException;
    public String getServerUsuario (String nombre) throws RemoteException;
    public float getTotalDonado (String usuario) throws RemoteException;
}