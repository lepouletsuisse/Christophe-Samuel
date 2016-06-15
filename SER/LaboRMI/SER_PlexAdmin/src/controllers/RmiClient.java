package controllers;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;

import ch.heigvd.iict.cours.ser.imdb.models.Data;
import ch.heigvd.iict.cours.ser.rmi.IClientApi;
import ch.heigvd.iict.cours.ser.rmi.IServerApi;

/**
 * @author https://sites.google.com/site/jamespandavan/Home/java/sample-remote-observer-based-on-rmi
 */
public class RmiClient extends UnicastRemoteObject implements IClientApi {

	private static final long serialVersionUID = -8478788162368553187L;
	private ControleurGeneral cont;
	
	private IServerApi remoteService = null;

	protected RmiClient(IServerApi remoteService, ControleurGeneral cont) throws RemoteException {
		super();
		this.cont = cont;
		this.remoteService = remoteService;
	}
	
	protected void initialConnection() throws RemoteException {
		//we register to server
		remoteService.addObserver(this);
		
		//display
		System.out.println("Initial request: ");
	}
	
	protected void startCheckingThread() {
		//we start a thread to periodically check if the server is available
		Thread thread = new Thread(){
			@Override
			public void run() {
				boolean isStillConnectedToServer = true;
				while(isStillConnectedToServer) {
					//every 10 seconds
					try {
						Thread.sleep(10 * 1000);
					} catch (InterruptedException e) { }
					try {
						isStillConnectedToServer = remoteService.isStillConnected();
					} catch (RemoteException e) {
						isStillConnectedToServer = false;
					}
				}
				System.err.println("Server is not avalaible anymore, we stop client");
				System.exit(1);
			};
		};
		thread.start();
	}
	
	/*
	 * API - RemoteObserver implementation
	 */
	@Override
	public void update(Object observable, Signal signalType, Data newData) throws RemoteException {

		cont.initBaseDeDonneesAvecNouvelleVersion(newData);
		System.out.println("Update request: ");
		
	}

}
