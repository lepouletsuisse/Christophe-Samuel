-- Set the global values for easy insert

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

USE domotique;


-- Truncate all the table

truncate table adresse;
truncate table anemometre;
truncate table capteur;
truncate table consommation;
truncate table droit_entree;
truncate table droit_utilisation;
truncate table enfant;
truncate table etat;
truncate table hist_deplacement;
truncate table hist_utilisation;
truncate table luxmetre;
truncate table maison;
truncate table objet;
truncate table objet_passif;
truncate table objet_utilisable;
truncate table parent;
truncate table piece;
truncate table presence;
truncate table proprietaire;
truncate table thermometre;
truncate table utilisateur;
truncate table utilisateur_nom;
truncate table utilisateur_prenom;
truncate table visiteur;

-- Users

	-- Samuel (propriétaire)
insert into utilisateur values(1,"M", 123456, "1994-04-16");
insert into utilisateur_nom values(1, "Darcey");
insert into utilisateur_prenom values(1, "Samuel");
insert into proprietaire values(1,1);

	-- Jean (Parent M)
insert into utilisateur values(2,"M", 123457, "1987-02-01");
insert into utilisateur_nom values(2, "Smith");
insert into utilisateur_prenom values(2, "Jean");
insert into utilisateur_prenom values(2, "Jacques");
insert into parent values(2,3);

	-- Marie (Parent F)
insert into utilisateur values(3,"F", 123458, "1988-12-25");
insert into utilisateur_nom values(3, "Smith");
insert into utilisateur_nom values(3, "Baumgartner");
insert into utilisateur_prenom values(3, "Marie");
insert into utilisateur_prenom values(3, "Jeanne");
insert into utilisateur_prenom values(3, "Anne");
insert into parent values(3,3);

	-- Cindy (Enfant F)
insert into utilisateur values(4,"F", 123459, "1999-08-30");
insert into utilisateur_nom values(4, "Smith");
insert into utilisateur_prenom values(4, "Cindy");
insert into utilisateur_prenom values(4, "Camille");
insert into enfant values(4,4);

	-- Christophe (Visiteur M)
insert into utilisateur values(5,"M", 123460, "1987-10-26");
insert into utilisateur_nom values(5, "Peretti");
insert into utilisateur_prenom values(5, "Christophe");
insert into visiteur values(5, now(), now(), 5);

-- Adresses

insert into adresse values(1, "Châbles", 1474, "Route de Béthanie", 45);

insert into adresse values(2, "Yverdon", 1400, "Rue du centre", 2);

insert into adresse values(3, "Yvonand", 1462, "Rue des poules", 35);

insert into adresse values(4, "Lausanne", 1000, "Rue du flon", 5);

insert into adresse values(5, "Lausanne", 1000, "Rue du centre", 26);

-- Rooms

insert into piece values(1, 1, "Cuisine", "Cuisine", 10, "F");

insert into piece values(2, 1, "Chambre des parents", "Chambre", 14, "F");

insert into piece values(3, 1, "Chambre de Cindy", "Chambre", 9, "F");

insert into piece values(4, 1, "Chambre d'invités", "Chambre", 12, "F");

insert into piece values(5, 1, "Jardin", "Jardin", -1, "T");

insert into piece values(6, 1, "Salle de bain 1er étage", "Salle de bain", 6, "F");

insert into piece values(7, 1, "Salle de bain 2ieme étage", "Salle de bain", 6, "F");

insert into piece values(8, 1, "Grenier", "Grenier", 20, "F");

insert into piece values(9, 1, "Cave", "Cave", 25, "F");

-- Home

insert into maison values(1, "Smith", 3, 9, 2);

-- States

insert into etat values(1, "OFF");
insert into etat values(2, "ON");
insert into etat values(3, "En marche");

-- Objects

insert into objet values(1, 1, "Machine à café", current_date(), 1);
insert into objet_utilisable values(1, 0);

insert into objet values(2, 1, "Micro-onde", current_date(), 1);
insert into objet_utilisable values(2, 0);

insert into objet values(3, 2, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(3, 0);
insert into objet_passif values(3);

insert into objet values(4, 2, "Lampe 2", current_date(), 1);
insert into objet_utilisable values(4, 0);
insert into objet_passif values(4);

insert into objet values(5, 2, "Lampe 3", current_date(), 1);
insert into objet_utilisable values(5, 0);
insert into objet_passif values(5);

insert into objet values(6, 2, "Ordinateur", current_date(), 1);
insert into objet_utilisable values(6, 0);

insert into objet values(7, 3, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(7, 0);
insert into objet_passif values(7);

insert into objet values(8, 3, "Lampe 2", current_date(), 1);
insert into objet_utilisable values(8, 0);
insert into objet_passif values(8);

insert into objet values(9, 4, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(9, 0);
insert into objet_passif values(9);

insert into objet values(10, 5, "Tondeuse électrique", current_date(), 1);
insert into objet_utilisable values(10, 0);

insert into objet values(11, 5, "Arrosage", current_date(), 1);
insert into objet_passif values(11);

insert into objet values(12, 6, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(12, 0);
insert into objet_passif values(12);

insert into objet values(13, 6, "Douche", current_date(), 1);
insert into objet_utilisable values(13, 0);

insert into objet values(14, 7, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(14, 0);
insert into objet_passif values(14);

insert into objet values(15, 7, "Douche", current_date(), 1);
insert into objet_utilisable values(15, 0);

insert into objet values(16, 8, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(16, 0);
insert into objet_passif values(16);

insert into objet values(17, 9, "Lampe 1", current_date(), 1);
insert into objet_utilisable values(17, 0);
insert into objet_passif values(17);

insert into objet values(18, 9, "Chauffage", current_date(), 1);
insert into objet_passif values(18);

insert into objet values(19, 9, "Machine à laver", current_date(), 1);
insert into objet_utilisable values(19, 0);

-- Consommation

insert into consommation values(1, 1, "Electricité [W/h]", 400);
insert into consommation values(2, 2, "Electricité [W/h]", 650);
insert into consommation values(3, 3, "Electricité [W/h]", 20);
insert into consommation values(4, 4, "Electricité [W/h]", 20);
insert into consommation values(5, 5, "Electricité [W/h]", 20);
insert into consommation values(6, 6, "Electricité [W/h]", 900);
insert into consommation values(7, 7, "Electricité [W/h]", 20);
insert into consommation values(8, 8, "Electricité [W/h]", 20);
insert into consommation values(9, 9, "Electricité [W/h]", 20);
insert into consommation values(10, 10, "Electricité [W/h]", 800);
insert into consommation values(11, 11, "Electricité [W/h]", 100);
insert into consommation values(11, 12, "Eau [l/h]", 50);
insert into consommation values(12, 13, "Electricité [W/h]", 20);
insert into consommation values(13, 14, "Eau [l/h]", 100);
insert into consommation values(14, 15, "Electricité [W/h]", 20);
insert into consommation values(15, 16, "Eau [l/h]", 100);
insert into consommation values(16, 17, "Electricité [W/h]", 20);
insert into consommation values(17, 18, "Electricité [W/h]", 20);
insert into consommation values(18, 19, "Mazout [l/h]", 12);
insert into consommation values(19, 20, "Eau [l/h]", 150);
insert into consommation values(20, 21, "Electricité [W/h]", 700);

-- Access permission

	-- Samuel (Proprietaire M)
insert into droit_entree values(1, 1);
insert into droit_entree values(1, 2);
insert into droit_entree values(1, 3);
insert into droit_entree values(1, 4);
insert into droit_entree values(1, 5);
insert into droit_entree values(1, 6);
insert into droit_entree values(1, 7);
insert into droit_entree values(1, 8);
insert into droit_entree values(1, 9);

	-- Jean (Parent M)
insert into droit_entree values(2, 1);
insert into droit_entree values(2, 2);
insert into droit_entree values(2, 3);
insert into droit_entree values(2, 4);
insert into droit_entree values(2, 5);
insert into droit_entree values(2, 6);
insert into droit_entree values(2, 7);
insert into droit_entree values(2, 8);
insert into droit_entree values(2, 9);
    
    -- Marie (Parent F)
insert into droit_entree values(3, 1);
insert into droit_entree values(3, 2);
insert into droit_entree values(3, 3);
insert into droit_entree values(3, 4);
insert into droit_entree values(3, 5);
insert into droit_entree values(3, 6);
insert into droit_entree values(3, 7);
insert into droit_entree values(3, 8);
insert into droit_entree values(3, 9);
    
    -- Cindy (Enfant F)
insert into droit_entree values(4, 1);
insert into droit_entree values(4, 3);
insert into droit_entree values(4, 5);
insert into droit_entree values(4, 6);
    
    -- Christophe (Invite M)
insert into droit_entree values(5, 1);
insert into droit_entree values(5, 4);
insert into droit_entree values(5, 5);
insert into droit_entree values(5, 6);

-- Use permission
	-- Samuel (Proprietaire M)
insert into droit_utilisation values(1, 1);
insert into droit_utilisation values(1, 2);
insert into droit_utilisation values(1, 3);
insert into droit_utilisation values(1, 4);
insert into droit_utilisation values(1, 5);
insert into droit_utilisation values(1, 6);
insert into droit_utilisation values(1, 7);
insert into droit_utilisation values(1, 8);
insert into droit_utilisation values(1, 9);
insert into droit_utilisation values(1, 10);
insert into droit_utilisation values(1, 11);
insert into droit_utilisation values(1, 12);
insert into droit_utilisation values(1, 13);
insert into droit_utilisation values(1, 14);
insert into droit_utilisation values(1, 15);
insert into droit_utilisation values(1, 16);
insert into droit_utilisation values(1, 17);
insert into droit_utilisation values(1, 18);
insert into droit_utilisation values(1, 19);

	-- Jean (Parent M)
insert into droit_utilisation values(2, 1);
insert into droit_utilisation values(2, 2);
insert into droit_utilisation values(2, 3);
insert into droit_utilisation values(2, 4);
insert into droit_utilisation values(2, 5);
insert into droit_utilisation values(2, 6);
insert into droit_utilisation values(2, 7);
insert into droit_utilisation values(2, 8);
insert into droit_utilisation values(2, 9);
insert into droit_utilisation values(2, 10);
insert into droit_utilisation values(2, 11);
insert into droit_utilisation values(2, 12);
insert into droit_utilisation values(2, 13);
insert into droit_utilisation values(2, 14);
insert into droit_utilisation values(2, 15);
insert into droit_utilisation values(2, 16);
insert into droit_utilisation values(2, 17);
insert into droit_utilisation values(2, 18);
insert into droit_utilisation values(2, 19);
    
    -- Marie (Parent F)
insert into droit_utilisation values(3, 1);
insert into droit_utilisation values(3, 2);
insert into droit_utilisation values(3, 3);
insert into droit_utilisation values(3, 4);
insert into droit_utilisation values(3, 5);
insert into droit_utilisation values(3, 6);
insert into droit_utilisation values(3, 7);
insert into droit_utilisation values(3, 8);
insert into droit_utilisation values(3, 9);
insert into droit_utilisation values(3, 10);
insert into droit_utilisation values(3, 11);
insert into droit_utilisation values(3, 12);
insert into droit_utilisation values(3, 13);
insert into droit_utilisation values(3, 14);
insert into droit_utilisation values(3, 15);
insert into droit_utilisation values(3, 16);
insert into droit_utilisation values(3, 17);
insert into droit_utilisation values(3, 18);
insert into droit_utilisation values(3, 19);
    
    -- Cindy (Enfant F)
insert into droit_utilisation values(4, 3);
insert into droit_utilisation values(4, 4);
insert into droit_utilisation values(4, 5);
insert into droit_utilisation values(4, 7);
insert into droit_utilisation values(4, 8);
insert into droit_utilisation values(4, 9);
insert into droit_utilisation values(4, 12);
insert into droit_utilisation values(4, 13);
insert into droit_utilisation values(4, 14);
insert into droit_utilisation values(4, 15);
insert into droit_utilisation values(4, 16);
insert into droit_utilisation values(4, 17);
    
    -- Christophe (Invite M)
insert into droit_utilisation values(5, 1);
insert into droit_utilisation values(5, 2);
insert into droit_utilisation values(5, 3);
insert into droit_utilisation values(5, 4);
insert into droit_utilisation values(5, 5);
insert into droit_utilisation values(5, 7);
insert into droit_utilisation values(5, 8);
insert into droit_utilisation values(5, 9);
insert into droit_utilisation values(5, 12);
insert into droit_utilisation values(5, 13);
insert into droit_utilisation values(5, 14);
insert into droit_utilisation values(5, 15);
insert into droit_utilisation values(5, 16);
insert into droit_utilisation values(5, 17);

-- Sensor

insert into capteur values(1, 1);
insert into presence values(1, 0);

insert into capteur values(2, 1);
insert into thermometre values(2, 18);

insert into capteur values(3, 1);
insert into luxmetre values(3, 10);

insert into capteur values(4, 5);
insert into anemometre values(4, 10);

-- Re set the global values

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;