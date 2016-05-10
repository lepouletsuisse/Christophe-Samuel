package controllers;

import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import com.google.gson.JsonPrimitive;
import com.google.gson.JsonArray;

import models.*;
import views.*;

public class ControleurMedia {

	private ControleurGeneral ctrGeneral;
	private static MainGUI mainGUI;
	private ORMAccess ormAccess;

	private GlobalData globalData;

	public ControleurMedia(ControleurGeneral ctrGeneral, MainGUI mainGUI, ORMAccess ormAccess) {
		this.ctrGeneral = ctrGeneral;
		ControleurMedia.mainGUI = mainGUI;
		this.ormAccess = ormAccess;
	}

	public void sendJSONToMedia() {
		new Thread() {
			public void run() {
				mainGUI.setAcknoledgeMessage("Envoi JSON ... WAIT");
				// long currentTime = System.currentTimeMillis();

				JsonObject objCin = new JsonObject();
				JsonObject objProjections = new JsonObject();
				
				JsonArray tabProj = new JsonArray();
				boolean trouve = false;
				try {
					globalData = ormAccess.GET_GLOBAL_DATA();

					SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

					
					for (Projection proj : globalData.getProjections()) {
						JsonObject objProj = new JsonObject();

						objProj.add("id", new JsonPrimitive(proj.getId()));
						objProj.add("titre", new JsonPrimitive(proj.getFilm().getTitre()));
						objProj.add("date", new JsonPrimitive(df.format(proj.getDateHeure().getTime())));

						JsonArray tabActeurs = new JsonArray();
						for (RoleActeur role : proj.getFilm().getRoles()) {
							trouve = false;
							JsonObject objActeur = new JsonObject();
							if(role.getPlace() == 1){
								objActeur.add("Place " + Long.toString(role.getPlace()), new JsonPrimitive(role.getActeur().getNom()));
								tabActeurs.add(objActeur);
								if (trouve) break;
								trouve = true;
							} else if(role.getPlace() == 2){
								objActeur.add("Place " + Long.toString(role.getPlace()), new JsonPrimitive(role.getActeur().getNom()));
								tabActeurs.add(objActeur);
								if (trouve) break;
								trouve = true;
							}
							

							
						}
						objProj.add("acteurs", tabActeurs);
						tabProj.add(objProj);
						objProjections.add("Projections", tabProj);
						objCin.add("cinema", objProjections);
					}

					writeJSON(objCin, "parsedData.json");
					mainGUI.setAcknoledgeMessage("Genreation JSON OK");
				} catch (Exception e) {
					mainGUI.setErrorMessage("Construction JSON impossible", e.toString());
				}
			}
		}.start();
	}

	private void writeJSON(Object obj, String name) throws IOException {
		Gson gson = new GsonBuilder().serializeNulls().setPrettyPrinting().create();
		String jsonOutput = gson.toJson(obj);

		FileWriter writer = new FileWriter(name);
		writer.write(jsonOutput);
		writer.close();
	}

}