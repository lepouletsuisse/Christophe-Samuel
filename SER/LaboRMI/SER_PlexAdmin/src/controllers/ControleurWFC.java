package controllers;

import java.rmi.Naming;

import ch.heigvd.iict.cours.ser.rmi.IServerApi;
import views.*;

public class ControleurWFC {

	private ControleurGeneral ctrGeneral;
	private static MainGUI mainGUI;

	public ControleurWFC(ControleurGeneral ctrGeneral, MainGUI mainGUI){
		this.ctrGeneral=ctrGeneral;
		ControleurWFC.mainGUI=mainGUI;
		
		try {
			//we connect to server
			IServerApi remoteService = (IServerApi) Naming.lookup("//localhost:9999/RmiService");

			//we start client
			RmiClient client = new RmiClient(remoteService, ctrGeneral);
			client.initialConnection();
			client.startCheckingThread();
			
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}


}