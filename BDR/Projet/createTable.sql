DROP schema if exists domotique;
CREATE DATABASE domotique;
USE domotique;

CREATE TABLE adresse(
	id int NOT NULL AUTO_INCREMENT,
    ville varchar(64) NOT NULL,
    npa int NOT NULL,
    rue varchar(64) NOT NULL,
    numero int NOT NULL,
    
    primary key(id)
);

CREATE TABLE maison (
	id int NOT NULL AUTO_INCREMENT,
	nom_famille varchar(64),
    nb_personne int,
    nb_piece int NOT NULL,
    adresse_id int NOT NULL,
    
	primary key (id),
    constraint fk__maison_adresse foreign key (adresse_id) references adresse(id) on delete restrict on update cascade
    );

CREATE TABLE piece (
	id int NOT NULL AUTO_INCREMENT,
    maison_id int NOT NULL,
    nom varchar(64) NOT NULL,
    type_piece varchar(64) NOT NULL,
    superficie int,
    estExterieur char(1) NOT NULL,
    
    primary key (id),
    constraint fk_piece_maison foreign key (maison_id) references maison(id) on delete cascade on update cascade
);

CREATE TABLE utilisateur(
	id int NOT NULL AUTO_INCREMENT,
    sexe char(1) NOT NULL,
    avs int NOT NULL UNIQUE,
    naissance DATE NOT NULL,
    
    primary key (id)
);

CREATE TABLE utilisateur_prenom(
	utilisateur_id int NOT NULL,
    prenom varchar(64) NOT NULL,
    
    primary key (utilisateur_id, prenom),
    constraint fk__utilisateur_prenom_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade
);

CREATE TABLE utilisateur_nom(
	utilisateur_id int NOT NULL,
    nom varchar(64) NOT NULL,
    
    primary key (utilisateur_id, nom),
    constraint fk__utilisateur_nom_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade
);

CREATE TABLE visiteur(
	utilisateur_id int,
    date_arrivee DATE NOT NULL,
    date_depart DATE NOT NULL,
    adresse_id int NOT NULL,
    
    primary key(utilisateur_id),
    constraint fk_visiteur_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_visiteur_adresse foreign key (adresse_id) references adresse(id) on delete restrict on update cascade
);

CREATE TABLE enfant(
	utilisateur_id int,
    adresse_ecole_id int NOT NULL,
    
    primary key(utilisateur_id),
	constraint fk_enfant_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_enfant_adresse foreign key (adresse_ecole_id) references adresse(id) on delete cascade on update cascade
);

CREATE TABLE parent(
	utilisateur_id int,
    adresse_job_id int NOT NULL,
    
    primary key(utilisateur_id),
	constraint fk_parent_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_parent_adresse foreign key (adresse_job_id) references adresse(id) on delete restrict on update cascade
);

CREATE TABLE proprietaire(
	utilisateur_id int,
    adresse_id int NOT NULL,
    
    primary key(utilisateur_id),
	constraint fk_proprietaire_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_proprietaire_adresse foreign key (adresse_id) references adresse(id) on delete restrict on update cascade
);

CREATE TABLE capteur(
	id int NOT NULL AUTO_INCREMENT,
    piece_id int NOT NULL,
    
    primary key(id),
    constraint fk_capteur_piece foreign key (piece_id) references piece(id) on delete cascade on update cascade
);

CREATE TABLE presence(
	capteur_id int,
    nb_personne int,
    
    primary key(capteur_id),
    constraint fk_presence_capteur foreign key (capteur_id) references capteur(id) on delete cascade on update cascade
);

CREATE TABLE luxmetre(
	capteur_id int,
    nb_lux int,
    
    primary key(capteur_id),
    constraint fk_luxmetre_capteur foreign key (capteur_id) references capteur(id) on delete cascade on update cascade
);

CREATE TABLE thermometre(
	capteur_id int,
    degres_celsius int,
    
    primary key(capteur_id),
    constraint fk_thermometre_capteur foreign key (capteur_id) references capteur(id) on delete cascade on update cascade
);

CREATE TABLE anemometre(
	capteur_id int,
    km_h int,
    
    primary key(capteur_id),
    constraint fk_anemometre_capteur foreign key (capteur_id) references capteur(id) on delete cascade on update cascade
);

CREATE TABLE etat(
	id int NOT NULL AUTO_INCREMENT,
    nom varchar(64) NOT NULL UNIQUE,
    
    primary key (id)
);

CREATE TABLE objet(
	id int NOT NULL AUTO_INCREMENT,
    piece_id int NOT NULL,
    nom varchar(64) NOT NULL,
    date_aquisition DATE,
    etat_id int NOT NULL,
    
    primary key(id),
    constraint fk_objet_piece foreign key (piece_id) references piece(id) on delete cascade on update cascade,
    constraint fk_objet_etat foreign key (etat_id) references etat(id) on delete restrict on update cascade
);

CREATE TABLE objet_passif(
	objet_id int,
    
    primary key (objet_id),
    constraint fk_objet_passif_objet foreign key (objet_id) references objet(id) on delete cascade on update cascade
);

CREATE TABLE objet_utilisable(
	objet_id int,
    nb_utilisation int NOT NULL,
    
    primary key (objet_id),
    constraint fk_objet_utilisable_objet foreign key (objet_id) references objet(id) on delete cascade on update cascade
);

CREATE TABLE consommation(
	objet_id int,
    id int NOT NULL AUTO_INCREMENT,
    nom varchar(64) NOT NULL,
    quantite int,
    
    primary key (id),
    constraint fk_consommation_objet foreign key (objet_id) references objet(id) on delete cascade on update cascade
);

CREATE TABLE hist_deplacement(
	utilisateur_id int,
    presence_id int,
    date_entree DATETIME NOT NULL,
    date_sortie DATETIME NOT NULL,
    
    constraint fk_hist_deplacement_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_hist_deplacement_presence foreign key (presence_id) references presence(capteur_id) on delete cascade on update cascade
);

CREATE TABLE hist_utilisation(
	utilisateur_id int,
    objet_id int,
    date_debut DATETIME NOT NULL,
    date_fin DATETIME NOT NULL,
    
    constraint fk_hist_utilisation_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_hist_utilisation_objet foreign key (objet_id) references objet(id) on delete cascade on update cascade
);

CREATE TABLE droit_entree(
	utilisateur_id int,
    piece_id int,
    
    primary key (utilisateur_id, piece_id),
    constraint fk_droit_entree_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_droit_entree_piece foreign key (piece_id) references piece(id) on delete cascade on update cascade
);

CREATE TABLE droit_utilisation(
	utilisateur_id int,
    objet_id int,
    
    primary key (utilisateur_id, objet_id),
    constraint fk_droit_utilisation_utilisateur foreign key (utilisateur_id) references utilisateur(id) on delete cascade on update cascade,
    constraint fk_droit_utilisation_objet foreign key (objet_id) references objet(id) on delete cascade on update cascade
);