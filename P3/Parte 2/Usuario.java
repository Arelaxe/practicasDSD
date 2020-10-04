public class Usuario{
    private String nombre;
    private String pass;
    private boolean donacion = false;

    public Usuario(){
    }

    public void setNombre(String nombre){
        this.nombre = nombre;
    }

    public void setPass(String pass){
        this.pass = pass;
    }

    public void setDonacion(){
        donacion = true;
    }

    public String getNombre(){
        return nombre;
    }

    public String getPass(){
        return pass;
    }

    public boolean getDonacion(){
        return donacion;
    }
}