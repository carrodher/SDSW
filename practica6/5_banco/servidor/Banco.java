import java.rmi.*;
import java.util.*;

/* (1)
Define una interfaz que derive de la interfaz Remote y contiene los métodos requeridos
por el servicio, permitiendo usar la expcepción RemoteException que permite a RMI notificar
sobre errores relacionados con la comunicación. */
interface Banco extends Remote {
    Cuenta crearCuenta(Titular t) throws RemoteException;
    List<Cuenta> obtenerCuentas() throws RemoteException;
}