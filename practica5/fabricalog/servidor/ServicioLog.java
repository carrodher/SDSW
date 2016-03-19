import java.rmi.*;

/* (3)
Define una interfaz que deriva de la interfaz Remote y contiene los métodos requeridos
por el servicio, permitiendo usar la expcepción RemoteException que permite a RMI notificar
sobre errores relacionados con la comunicación. */
interface ServicioLog extends Remote {
    void log (String m) throws RemoteException;
}
