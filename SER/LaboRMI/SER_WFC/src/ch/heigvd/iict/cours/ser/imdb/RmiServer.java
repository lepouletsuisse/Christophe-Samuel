package ch.heigvd.iict.cours.ser.imdb;
import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;

import ch.heigvd.iict.cours.ser.imdb.models.Data;
import ch.heigvd.iict.cours.ser.rmi.IClientApi;
import ch.heigvd.iict.cours.ser.rmi.IClientApi.Signal;
import ch.heigvd.iict.cours.ser.rmi.IServerApi;

/**
 * @author https://sites.google.com/site/jamespandavan/Home/java/sample-remote-observer-based-on-rmi
 */
public class RmiServer extends Observable implements IServerApi {

    private Data data = null;
    
    public RmiServer(Data data) {
    	//we will access the list by different threads
    	this.data = data;
    }
    
    /*
     * API - RmiService implementation
     */
	
    @Override
    public void addObserver(IClientApi client) throws RemoteException {
        WrappedObserver wo = new WrappedObserver(client);
        addObserver(wo);
        System.out.println("Added observer: " + wo);
    }

    @Override
    public boolean isStillConnected() throws RemoteException {
    	return true;
    }
    
	@Override
	public Data getData() throws RemoteException {
		return this.data;
	}

	
	public void notifyClients(Data data){
		this.data = data;
		setChanged();
        notifyObservers(data);
	}

	
    /*
     *  Observer
     */
	private class WrappedObserver implements Observer, Serializable {

		private static final long serialVersionUID = -2067345842536415833L;
		
		private IClientApi ro = null;

        public WrappedObserver(IClientApi ro) {
            this.ro = ro;
        }

        @Override
        public void update(Observable o, Object arg) {
            try {
                ro.update(o.toString(), Signal.UPDATE_REQUESTED, (Data)arg);
            } catch (RemoteException e) {
                System.out.println("Remote exception removing observer: " + this);
                o.deleteObserver(this);
            }
        }
    }
	
}
