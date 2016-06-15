package ch.heigvd.iict.cours.ser.imdb;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

import ch.heigvd.iict.cours.ser.imdb.db.MySQLAccess;
import ch.heigvd.iict.cours.ser.imdb.models.Data;
import ch.heigvd.iict.cours.ser.rmi.IServerApi;

public class Main {
	static {
		
		
		// this will load the MySQL driver, each DB has its own driver
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			System.err.println("MySQL drivers not found !");
			System.exit(1);
		}

		//database configuration
		MySQLAccess.MYSQL_URL 		= "docr.iict.ch";
		MySQLAccess.MYSQL_DBNAME 	= "imdb";
		MySQLAccess.MYSQL_USER 		= "imdb";
		MySQLAccess.MYSQL_PASSWORD 	= "imdb";
	}

	private static Scanner scanner = new Scanner(System.in);
	private static RmiServer server;
	public static void main(String[] args) {
		Main main = new Main();
		
		try {
	        Registry rmiRegistry = LocateRegistry.createRegistry(9999);
	        server = new RmiServer(lastData);
	        IServerApi rmiService = (IServerApi) UnicastRemoteObject.exportObject(server, 9999);
	        rmiRegistry.bind("RmiService", rmiService);
	    } catch (Exception ex) {
	        ex.printStackTrace();
	    }
		
		main.run();
	}

	private static Data lastData = null;

	private void run() {

		boolean continuer = true;		
		while(continuer) {
			System.out.print("Select the data version to download [1/2/3/0=quit]: ");
			int choice = -1;
			try {
				choice = scanner.nextInt();
			} catch(Exception e) {
				e.printStackTrace();
			}
			
			if(choice == 0) continuer = false;
			else if(choice >= 1 && choice <= 3) {
				Worker worker = new Worker(choice);
				this.lastData = worker.run();

				server.notifyClients(lastData);
				
			}
		}
	}

}
