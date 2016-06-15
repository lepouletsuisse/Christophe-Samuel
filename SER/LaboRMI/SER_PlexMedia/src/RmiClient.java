import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;

import javax.xml.crypto.Data;

import api.IClientApi2;
import api.IServerApi2;

/**
 * @author https://sites.google.com/site/jamespandavan/Home/java/sample-remote-observer-based-on-rmi
 */
public class RmiClient extends UnicastRemoteObject implements IClientApi2 {

	public static void main(String [] args) {
		try {
			
			//we connect to server
			remoteService = (IServerApi2) Naming.lookup("//localhost:8888/RmiService");

			//we start client
			RmiClient client = new RmiClient(remoteService);
			client.initialConnection();
			client.startCheckingThread();
			
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		
		
	}
	
	public void getData(){
		try {
			// On affiche dans la console le JSon des projections
			System.out.println(remoteService.getData());
			deserialize(remoteService.getData());
		} catch (RemoteException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private static final long serialVersionUID = -8478788162368553187L;
	
	private static IServerApi2 remoteService = null;

	protected RmiClient(IServerApi2 remoteService) throws RemoteException {
		super();
		RmiClient.remoteService = remoteService;
		ClientGUI clientGui = new ClientGUI(this);
	}
	
	protected void initialConnection() throws RemoteException {
		//we register to server
		remoteService.addObserver(this);
		
		//display
		System.out.println("Press button to get Data: ");
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
	public void deserialize(String json){
		int a = 1;
		int b;
		do{
			b = json.indexOf('"',a + 1);
			String name = json.substring(a + 1, b);
			a = json.indexOf('"',b + 1);
			
			switch(name){
				case "cinema":
				case "Projections":
					System.out.println(name);
					break;
				case "titre":
				case "date":
					System.out.print("\t" + name + " \t\t\t: ");
					break;
				case "acteurs":
					System.out.println("\t" + name);
					break;
				case "Place 1":
				case "Place 2":
					System.out.print("\t\t" + name + " \t: ");
					break;
				case "id":
					System.out.print("\t" + name + " \t\t\t: ");
					System.out.println(json.substring(b + 2, b + 3));
					break;
				default:
					System.out.println(name);
			}
		}while(b > 0 && a > 0);
	}

}
