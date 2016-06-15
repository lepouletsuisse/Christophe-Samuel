package controllers;

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

import api.IServerApi2;
import api.IClientApi2;
import api.IClientApi2.Signal;
import ch.heigvd.iict.cours.ser.imdb.models.Data;

/**
 * @author https://sites.google.com/site/jamespandavan/Home/java/sample-remote-observer-based-on-rmi
 */
public class RmiServer extends Observable implements IServerApi2 {

    private Data data = null;
    private ControleurGeneral cont;
    public RmiServer(ControleurGeneral cont) {
    	this.cont = cont;
    	//we will access the list by different threads
    	this.data = data;
    }
    

    @Override
    public boolean isStillConnected() throws RemoteException {
    	return true;
    }
    
	@Override
	public String getData() throws RemoteException {
		return this.cont.sendJSONToMedia();
	}


	@Override
	public void addObserver(IClientApi2 client) throws RemoteException {
		WrappedObserver wo = new WrappedObserver(client);
        addObserver(wo);
        System.out.println("Added observer: " + wo);
		
	}
	
	/*
     *  Observer
     */
	private class WrappedObserver implements Observer, Serializable {

		private static final long serialVersionUID = -2067345842536415833L;
		
		private IClientApi2 ro = null;

        public WrappedObserver(IClientApi2 ro) {
            this.ro = ro;
        }

        @Override
        public void update(Observable o, Object arg) {
        	/*
            try {
                ro.update(o.toString(), Signal.UPDATE_REQUESTED, (Data)arg);
            } catch (RemoteException e) {
                System.out.println("Remote exception removing observer: " + this);
                o.deleteObserver(this);
            }
            */
        }
    }
	
}
