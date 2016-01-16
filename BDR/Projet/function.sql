use domotique;

drop function if exists countAccess; 
DELIMITER //

create function countAccess(utilisateurId int, pieceId int)
returns int
begin
declare nombre int;

select count(*) into nombre from 
	hist_deplacement
    inner join utilisateur on utilisateur.id = hist_deplacement.utilisateur_id
    inner join capteur on capteur.id = hist_deplacement.presence_id
    inner join piece on capteur.piece_id = piece.id
    where utilisateur_id = utilisateurId 
		and piece.id = pieceId;
return nombre;
end; //
DELIMITER ;


drop function if exists countUse; 
DELIMITER //

create function countUse(utilisateurId int, objetId int)
returns int
begin
declare nombre int;

select count(*) into nombre from 
	hist_utilisation
    inner join utilisateur on utilisateur.id = hist_utilisation.utilisateur_id
    inner join objet on objet.id = hist_utilisation.objet_id
    where utilisateur_id = utilisateurId 
		and objet.id = objetId;
return nombre;
end; //
DELIMITER ;