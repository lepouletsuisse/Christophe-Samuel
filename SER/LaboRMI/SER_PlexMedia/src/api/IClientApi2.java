package api;


import java.rmi.Remote;
import java.rmi.RemoteException;

import ch.heigvd.iict.cours.ser.imdb.models.Data;
/**
 * @author https://sites.google.com/site/jamespandavan/Home/java/sample-remote-observer-based-on-rmi
 */
public interface IClientApi2 extends Remote {
	
	public enum Signal {
		UPDATE_REQUESTED
	}
	
	//void update(Object observable, Signal signalType, Data newData) throws RemoteException;

}
