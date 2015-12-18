use domotique;

drop view if exists view_objetEtat;
create view view_objetEtat as
	select objet.id as id_objet, 
			objet.nom as Objet, 
            etat.id as id_etat, 
            etat.nom as Etat, 
            piece.id as id_piece, 
            piece.nom as Piece
		from objet 
			inner join etat on objet.etat_id = etat.id
            inner join Piece on objet.piece_id = piece.id
            
;

drop view if exists view_utilisateurAdresse;
create view view_utilisateurAdresse as
	select adresse.id as id_adresse, 
			adresse.ville as Ville, 
			adresse.npa as NPA, 
            adresse.rue as Rue, 
            adresse.numero as Numero,
            utilisateur_nom.nom as Nom,
            utilisateur_prenom.prenom as Prenom,
            utilisateur.id as id_utilisateur
            
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
            
select * from view_utilisateurAdresse;
select * from droit_entree;