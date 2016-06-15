package api;


import java.rmi.Remote;
import java.rmi.RemoteException;

import ch.heigvd.iict.cours.ser.imdb.models.Data;

/**
 * @author https://sites.google.com/site/jamespandavan/Home/java/sample-remote-observer-based-on-rmi
 */
public interface IServerApi2 extends Remote {

	/**
	 * Method used by clients to register on the server
	 * @param client The client
	 * @throws RemoteException
	 */
	void addObserver(IClientApi2 client) throws RemoteException;
	
	/**
	 * Method used by clients to check the connection with the server
	 * @return true is the server is reachable
	 * @throws RemoteException
	 */
	boolean isStillConnected() throws RemoteException;
	
	/**
	 * Method used by clients to get all the data
	 * @return The data
	 * @throws RemoteException
	 */
	String getData() throws RemoteException;
	
}
