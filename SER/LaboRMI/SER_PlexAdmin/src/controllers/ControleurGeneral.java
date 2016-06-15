package controllers;

import views.*;

import ch.heigvd.iict.cours.ser.imdb.models.*;

// Pour XStream
import com.thoughtworks.xstream.*;

import api.IServerApi2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.net.URLDecoder;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Map;

public class ControleurGeneral {

	private static MainGUI mainGUI;
	private static MainGUI clientGUI;
	private static ORMAccess ormAccess;
	private ControleurProjections ctrProjections; 
	private ControleurFilms ctrFilms;
	private ControleurWFC ctrClient;

	//private ControleurWFC ctrWFC;
	private ControleurMedia ctrMedia; 
	private ControleurXMLCreation ctrXMLCreation;

	public ControleurGeneral(ORMAccess ormAccess){
		ControleurGeneral.ormAccess = ormAccess;
		mainGUI = new MainGUI(this);
		ctrProjections = new ControleurProjections(ormAccess, mainGUI);
		ctrFilms = new ControleurFilms(ormAccess, mainGUI);
		ctrProjections.refreshProjectionsList();
		ctrFilms.refreshFilmsList();

		ctrMedia = new ControleurMedia(this, mainGUI, ormAccess);
		ctrXMLCreation = new ControleurXMLCreation(this, mainGUI, ormAccess);
		ctrClient = new ControleurWFC(this, clientGUI);
		
		try {
            Registry rmiRegistry = LocateRegistry.createRegistry(8888);
            RmiServer server = new RmiServer(this);
            IServerApi2 rmiService = (IServerApi2) UnicastRemoteObject.exportObject(server, 8888);
            rmiRegistry.bind("RmiService", rmiService);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
		
	}

	public void createXStreamXML(){ctrXMLCreation.createXStreamXML();}

	public void createXML(){ctrXMLCreation.createXML();}

	public String sendJSONToMedia(){return ctrMedia.sendJSONToMedia();}

	public void initBaseDeDonnees() {
		new Thread(){
			public void run() {
				mainGUI.disableButtons();
				try {
					Data data = donneesDuFichierWFC_XML();

					ormAccess.initBD(data, mainGUI);

					ctrProjections.refreshProjectionsList();
					ctrFilms.refreshFilmsList();
					mainGUI.resetMessage();			
				}
				catch (Exception e ) {
					mainGUI.setErrorMessage("Erreur peuplement BD", e.toString());
				} 
				finally {
					mainGUI.enableButtons();
				}
			}
		}.start();
	}
	
	public void initBaseDeDonneesFromWFC(Data data) {
		final Data fData = data;
		new Thread(){
			public void run() {
				mainGUI.disableButtons();
				try {
					ormAccess.initBD(fData, mainGUI);

					ctrProjections.refreshProjectionsList();
					ctrFilms.refreshFilmsList();
					mainGUI.resetMessage();			
				}
				catch (Exception e ) {
					mainGUI.setErrorMessage("Erreur peuplement BD", e.toString());
				} 
				finally {
					mainGUI.enableButtons();
				}
			}
		}.start();
	}

	public void initBaseDeDonneesAvecNouvelleVersion(final Data data) {
		new Thread(){
			public void run() {
				mainGUI.disableButtons();
				mainGUI.setAcknoledgeMessage("Init BD");
				try {
					ormAccess.initBDAvecNouvellesVersionWFC(data, mainGUI);

					ctrProjections.refreshProjectionsList();
					ctrFilms.refreshFilmsList();
					mainGUI.resetMessage();			
				}
				catch (Exception e ) {
					mainGUI.setErrorMessage("Erreur peuplement BD", e.toString());
				} 
				finally {
					mainGUI.enableButtons();
				}
			}
		}.start();
	}

	@SuppressWarnings("unchecked")
	public Data donneesDuFichierWFC_XML() throws Exception {
		// Désérialisation du fichier XStream
		XStream xstream = new XStream();
		System.out.println("Chargement du contenu XML... ");
		mainGUI.setAcknoledgeMessage("Chargement du contenu XML... ");
		Data data = new Data();
		java.net.URL urlMoviesFile = ORMAccess.class.getResource("/resources/movies_v1.xml");
		java.net.URL urlPersonsFile = ORMAccess.class.getResource("/resources/persons_v1.xml");
		data.setPersons((Map<Long, Person>)readFromFile(URLDecoder.decode(urlPersonsFile.getPath()), xstream));
		data.setMovies((Map<Long, Movie>)readFromFile(URLDecoder.decode(urlMoviesFile.getPath()), xstream));
		System.out.println("Chargement du contenu XML: OK");
		return data;
	}

	private Object readFromFile(String filename, XStream serializer) {
		Object result = null;
		try {
			BufferedReader in = new BufferedReader(new FileReader(filename));
			result = serializer.fromXML(in);
			in.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return result;
	}

	public boolean isAlive() { return mainGUI != null; }
}