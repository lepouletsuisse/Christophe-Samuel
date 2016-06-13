package controllers;

import models.*;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.XMLWriter;
import views.*;

import java.io.*;
import java.sql.Timestamp;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.stream.Collectors;

import com.thoughtworks.xstream.XStream;

public class ControleurXMLCreation {

    //private ControleurGeneral ctrGeneral;
    private static MainGUI mainGUI;
    private ORMAccess ormAccess;

    private GlobalData globalData;

    public ControleurXMLCreation(ControleurGeneral ctrGeneral, MainGUI mainGUI, ORMAccess ormAccess) {
        //this.ctrGeneral=ctrGeneral;
        ControleurXMLCreation.mainGUI = mainGUI;
        this.ormAccess = ormAccess;
    }

    public void createXML() {
        new Thread() {
            public void run() {
                mainGUI.setAcknoledgeMessage("Creation XML... WAIT");
                long currentTime = System.currentTimeMillis();
                Document doc = DocumentHelper.createDocument();
                int noteTotale, nbNotes;
                double noteMoyenne;
                try {
                    globalData = ormAccess.GET_GLOBAL_DATA();

                    Element root = doc.addElement("cinema");
                    Element projections = root.addElement("projections");
                    for (Projection p : globalData.getProjections()) {
                        Element projection = projections.addElement("projection")
                                .addAttribute("id", Long.toString(p.getId()));
                        DateFormat df = new SimpleDateFormat("EEE MMM dd kk:mm:ss z yyyy", Locale.ENGLISH);
                        Date d = df.parse(p.getDateHeure().getTime().toString());
                        projection.addAttribute("date", (new Timestamp(d.getTime())).toString());
                        
                        projection.addElement("date")
                                .addText(p.getDateHeure().getTime().toString());
                        projection.addElement("numeroSalle")
                                .addText(p.getSalle().getNo());
                        Film f = p.getFilm();
                        Element film = projection.addElement("film")
                                .addAttribute("id", Long.toString(f.getId()));
                        Element titre = film.addElement("titre")
                                .addText(f.getTitre());
                        Element synopsis = film.addElement("synopsis")
                                .addText(f.getSynopsis());
                        film.addElement("duree")
                                .addText(Integer.toString(f.getDuree()));
                        
                        noteTotale = 0;
                        nbNotes = 0;
                        for(Critique c : f.getCritiques()){
                            noteTotale += c.getNote();
                            nbNotes++;
                        }
                        noteMoyenne = ((10 * noteTotale) / nbNotes) / 10.0;
                        film.addElement("noteMoyenne")
                        		.addText(Double.toString(noteMoyenne));
                        Element critiques = film.addElement("critiques");
                        for(Critique c : f.getCritiques()){
                            Element critique = critiques.addElement("critique");
                            critique.addElement("note").addText(Integer.toString(c.getNote()));
                            critique.addElement("texte").addText(c.getTexte());
                        }
                        film.addElement("genres").addText(f.getGenres().stream().map(Genre::getLabel).collect(Collectors.joining(", ")));
                        film.addElement("motCle").addText(f.getMotcles().stream().map(Motcle::getLabel).collect(Collectors.joining(", ")));
                        film.addElement("langages").addText(f.getLangages().stream().map(Langage::getLabel).collect(Collectors.joining(", ")));
                        if(f.getPhoto() != null){
                            film.addElement("image").addText(f.getPhoto());
                        }
                        Element roles = film.addElement("roles");
                        Element acteurs = projection.addElement("acteurs");
                        for(RoleActeur r : f.getRoles()){
                            Element role = roles.addElement("role")
                                    .addAttribute("place", Long.toString(r.getPlace()));
                            role.addElement("idActeur")
                                    .addText(Long.toString(r.getActeur().getId()));
                            role.addElement("personnage")
                                    .addText((r.getPersonnage() == null? "" : r.getPersonnage()));

                            Element acteur = acteurs.addElement("acteur").addAttribute("id", Long.toString(r.getActeur().getId()));
                            acteur.addElement("nom").addText(r.getActeur().getNom());
                            if(r.getActeur().getNomNaissance() != null){
                                acteur.addElement("nomNaissance").addText(r.getActeur().getNomNaissance());
                            }
                            acteur.addElement("biographie").addText((r.getActeur().getBiographie() == null
                                    ? "Unknown" : r.getActeur().getBiographie()));
                            acteur.addElement("sexe").addText(r.getActeur().getSexe().toString());
                            acteur.addElement("dateNaissance").addText((r.getActeur().getDateNaissance() == null
                                    ? "Unknown" : r.getActeur().getDateNaissance().getTime().toString()));
                            acteur.addElement("dateDeces").addText((r.getActeur().getDateDeces() == null
                                    ? "-" : r.getActeur().getDateDeces().getTime().toString()));

                        }

                    }

                    //return;
                } catch (Exception e) {
                    mainGUI.setErrorMessage("Construction XML impossible", e.toString());
                    System.out.println("Error: " + e.getMessage() + "\n");
                    e.printStackTrace();
                    System.exit(1);
                }

                try{
                    FileOutputStream out = new FileOutputStream("parsedData.xml");
                    OutputFormat outFormat = OutputFormat.createPrettyPrint();
                    XMLWriter output = new XMLWriter(out, outFormat);
                    output.write(doc);
                    output.flush();
                }catch(Exception e){
                    System.out.println("Error: " + e.getMessage());
                    System.exit(1);
                }
                System.out.println("Done [" + displaySeconds(currentTime, System.currentTimeMillis()) + "]");
                mainGUI.setAcknoledgeMessage("XML cree en " + displaySeconds(currentTime, System.currentTimeMillis()));

            }
        }.start();
    }

    public void createXStreamXML() {
        new Thread() {
            public void run() {
                mainGUI.setAcknoledgeMessage("Creation XML... WAIT");
                long currentTime = System.currentTimeMillis();
                try {
                    globalData = ormAccess.GET_GLOBAL_DATA();
                    globalDataControle();
                } catch (Exception e) {
                    mainGUI.setErrorMessage("Construction XML impossible", e.toString());
                }

                XStream xstream = new XStream();
                writeToFile("global_data.xml", xstream, globalData);
                System.out.println("Done [" + displaySeconds(currentTime, System.currentTimeMillis()) + "]");
                mainGUI.setAcknoledgeMessage("XML cree en " + displaySeconds(currentTime, System.currentTimeMillis()));
            }
        }.start();
    }

    private static void writeToFile(String filename, XStream serializer, Object data) {
        try {
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(filename), "UTF-8"));
            serializer.toXML(data, out);
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static final DecimalFormat doubleFormat = new DecimalFormat("#.#");

    private static final String displaySeconds(long start, long end) {
        long diff = Math.abs(end - start);
        double seconds = ((double) diff) / 1000.0;
        return doubleFormat.format(seconds) + " s";
    }

    private void globalDataControle() {
        for (Projection p : globalData.getProjections()) {
            System.out.println("******************************************");
            System.out.println(p.getFilm().getTitre());
            System.out.println(p.getSalle().getNo());
            System.out.println("Acteurs *********");
            for (RoleActeur role : p.getFilm().getRoles()) {
                System.out.println(role.getActeur().getNom());
            }
            System.out.println("Genres *********");
            for (Genre genre : p.getFilm().getGenres()) {
                System.out.println(genre.getLabel());
            }
            System.out.println("Mot-cles *********");
            for (Motcle motcle : p.getFilm().getMotcles()) {
                System.out.println(motcle.getLabel());
            }
            System.out.println("Langages *********");
            for (Langage langage : p.getFilm().getLangages()) {
                System.out.println(langage.getLabel());
            }
            System.out.println("Critiques *********");
            for (Critique critique : p.getFilm().getCritiques()) {
                System.out.println(critique.getNote());
                System.out.println(critique.getTexte());
            }
        }
    }
}



