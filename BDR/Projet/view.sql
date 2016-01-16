use domotique;

drop view if exists view_objetEtatConsommation;
create view view_objetEtatConsommation as
	select objet.id as id_objet, 
			objet.nom as Objet, 
            etat.id as id_etat, 
            etat.nom as Etat, 
            consommation.id as id_consommation,
            consommation.nom as NomConsommation,
            consommation.quantite as QuantiteConsommation,
            piece.id as id_piece, 
            piece.nom as Piece
		from objet 
			inner join etat on objet.etat_id = etat.id
			inner join consommation on objet.id = consommation.objet_id
            inner join piece on objet.piece_id = piece.id;

drop view if exists view_utilisateurAdresse;
create view view_utilisateurAdresse as
	select adresse.id as id_adresse, 
			adresse.ville as Ville, 
			adresse.npa as NPA, 
            adresse.rue as Rue, 
            adresse.numero as Numero,
            utilisateur_nom.nom as Nom,
            utilisateur_prenom.prenom as Prenom,
            utilisateur.id as id_utilisateur,
            utilisateur.naissance as Naissance
            
		from utilisateur
			left join proprietaire on utilisateur.id = proprietaire.utilisateur_id
            left join visiteur on utilisateur.id = visiteur.utilisateur_id
            left join enfant on utilisateur.id = enfant.utilisateur_id
            left join parent on utilisateur.id = parent.utilisateur_id
            inner join adresse on proprietaire.adresse_id = adresse.id
									or visiteur.adresse_id = adresse.id
                                    or enfant.adresse_ecole_id = adresse.id
                                    or parent.adresse_job_id = adresse.id
			inner join utilisateur_nom on utilisateur.id = utilisateur_nom.utilisateur_id
            inner join utilisateur_prenom on utilisateur.id = utilisateur_prenom.utilisateur_id;
		

drop view if exists view_thermometreData;
create view view_thermometreData as
	select capteur.id as id_capteur, 
			capteur.piece_id as id_piece, 
            piece.nom as Piece, 
            thermometre.degres_celsius as Degres
		from capteur
			inner join piece on capteur.piece_id = piece.id
            inner join thermometre on capteur.id = thermometre.capteur_id;

drop view if exists view_luxmetreData;
create view view_luxmetreData as
	select capteur.id as id_capteur, 
			capteur.piece_id as id_piece, 
            piece.nom as Piece, 
            luxmetre.nb_lux as Lux
		from capteur
			inner join piece on capteur.piece_id = piece.id
            inner join luxmetre on capteur.id = luxmetre.capteur_id;

drop view if exists view_anemometreData;
create view view_anemometreData as
	select capteur.id as id_capteur, 
			capteur.piece_id as id_piece, 
            piece.nom as Piece, 
            anemometre.km_h as VitesseVent
		from capteur
			inner join piece on capteur.piece_id = piece.id
            inner join anemometre on capteur.id = anemometre.capteur_id;

drop view if exists view_presenceData;
create view view_presenceData as
	select capteur.id as id_capteur, 
			capteur.piece_id as id_piece, 
            piece.nom as Piece, 
            presence.nb_personne as NbPersonne
		from capteur
			inner join piece on capteur.piece_id = piece.id
            inner join presence on capteur.id = presence.capteur_id;

