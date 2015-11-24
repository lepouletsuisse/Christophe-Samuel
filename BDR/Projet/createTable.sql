DROP schema if exists domotique;
CREATE DATABASE domotique;
USE domotique;

CREATE TABLE Adresse(
	id int,
    ville varchar(64) NOT NULL,
    npa int NOT NULL,
    rue varchar(64) NOT NULL,
    numero int NOT NULL,
    
    primary key(id)
);

CREATE TABLE Maison (
	id int,
	nom_famille varchar(64),
    nb_personne int,
    nb_piece int NOT NULL,
    adresse_id int,
    
	primary key (id),
    constraint fk__Maison_adresse foreign key (adresse_id) references Adresse(id) on delete restrict on update cascade
    );

CREATE TABLE Piece (
	id int,
    maison_id int,
    nom varchar(64) NOT NULL,
    type_piece varchar(64) NOT NULL,
    superficie int,
    estExterieur char(1) NOT NULL,
    
    primary key (id),
    constraint fk_Piece_maison foreign key (maison_id) references Maison(id) on delete cascade on update cascade
);

CREATE TABLE Utilisateur(
	id int,
    sexe char(1) NOT NULL,
    avs int NOT NULL UNIQUE,
    naissance DATE NOT NULL,
    
    primary key (id)
);

CREATE TABLE Utilisateur_Prenom(
	utilisateur_id int,
    prenom varchar(64),
    
    primary key (utilisateur_id, prenom),
    constraint fk__Utilisateur_Prenom_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade
);

CREATE TABLE Utilisateur_Nom(
	utilisateur_id int,
    nom varchar(64),
    
    primary key (utilisateur_id, nom),
    constraint fk__Utilisateur_Nom_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade
);

CREATE TABLE Visiteur(
	utilisateur_id int,
    date_arrivee DATE NOT NULL,
    date_depart DATE NOT NULL,
    adresse_id int,
    
    primary key(utilisateur_id),
    constraint fk_Visiteur_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Visiteur_adresse foreign key (adresse_id) references Adresse(id) on delete restrict on update cascade
);

CREATE TABLE Enfant(
	utilisateur_id int,
    adresse_ecole_id int,
    
    primary key(utilisateur_id),
	constraint fk_Enfant_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Enfant_adresse foreign key (adresse_ecole_id) references Adresse(id) on delete cascade on update cascade
);

CREATE TABLE Parent(
	utilisateur_id int,
    adresse_job_id int,
    
    primary key(utilisateur_id),
	constraint fk_Parent_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Parent_adresse foreign key (adresse_job_id) references Adresse(id) on delete restrict on update cascade
);

CREATE TABLE Proprietaire(
	utilisateur_id int,
    adresse_id int,
    
    primary key(utilisateur_id),
	constraint fk_Proprietaire_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Proprietaire_adresse foreign key (adresse_id) references Adresse(id) on delete restrict on update cascade
);

CREATE TABLE Capteur(
	id int,
    piece_id int,
    
    primary key(id),
    constraint fk_Capteur_piece foreign key (piece_id) references Piece(id) on delete cascade on update cascade
);

CREATE TABLE Presence(
	capteur_id int,
    nb_personne int,
    
    primary key(capteur_id),
    constraint fk_Presence_capteur foreign key (capteur_id) references Capteur(id) on delete cascade on update cascade
);

CREATE TABLE Luxmetre(
	capteur_id int,
    nb_lux int,
    
    primary key(capteur_id),
    constraint fk_Luxmetre_capteur foreign key (capteur_id) references Capteur(id) on delete cascade on update cascade
);

CREATE TABLE Thermometre(
	capteur_id int,
    degres_celsius int,
    
    primary key(capteur_id),
    constraint fk_Thermometre_capteur foreign key (capteur_id) references Capteur(id) on delete cascade on update cascade
);

CREATE TABLE Anemometre(
	capteur_id int,
    km_h int,
    
    primary key(capteur_id),
    constraint fk_Anemometre_capteur foreign key (capteur_id) references Capteur(id) on delete cascade on update cascade
);

CREATE TABLE Etat(
	id int,
    nom varchar(64) NOT NULL UNIQUE,
    
    primary key (id)
);

CREATE TABLE Objet(
	id int,
    piece_id int,
    nom varchar(64) NOT NULL,
    date_aquisition DATE,
    etat_id int,
    
    primary key(id),
    constraint fk_Objet_piece foreign key (piece_id) references Piece(id) on delete cascade on update cascade,
    constraint fk_Objet_etat foreign key (etat_id) references Etat(id) on delete restrict on update cascade
);

CREATE TABLE Objet_Passif(
	objet_id int,
    
    primary key (objet_id),
    constraint fk_Objet_Passif_objet foreign key (objet_id) references Objet(id) on delete cascade on update cascade
);

CREATE TABLE Objet_Utilisable(
	objet_id int,
    nb_utilisation int NOT NULL,
    
    primary key (objet_id),
    constraint fk_Objet_Utilisable_objet foreign key (objet_id) references Objet(id) on delete cascade on update cascade
);

CREATE TABLE Consommation(
	objet_id int,
    id int,
    nom varchar(64) NOT NULL,
    quantite int,
    
    primary key (objet_id, id),
    constraint fk_Consommation_objet foreign key (objet_id) references Objet(id) on delete cascade on update cascade
);

CREATE TABLE Hist_Deplacement(
	utilisateur_id int,
    presence_id int,
    date_entree DATETIME NOT NULL,
    date_sortie DATETIME NOT NULL,
    
    primary key (utilisateur_id, presence_id),
    constraint fk_Hist_Deplacement_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Hist_Deplacement_presence foreign key (presence_id) references Presence(capteur_id) on delete cascade on update cascade
);

CREATE TABLE Hist_Utilisation(
	utilisateur_id int,
    objet_id int,
    date_debut DATETIME NOT NULL,
    date_fin DATETIME NOT NULL,
    
    primary key (utilisateur_id, objet_id),
    constraint fk_Hist_Utilisation_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Hist_Utilisation_objet foreign key (objet_id) references Objet(id) on delete cascade on update cascade
);

CREATE TABLE Droit_Entree(
	utilisateur_id int,
    piece_id int,
    
    primary key (utilisateur_id, piece_id),
    constraint fk_Droit_Entree_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Droit_Entree_piece foreign key (piece_id) references Piece(id) on delete cascade on update cascade
);

CREATE TABLE Droit_Utilisation(
	utilisateur_id int,
    objet_id int,
    
    primary key (utilisateur_id, objet_id),
    constraint fk_Droit_Utilisation_utilisateur foreign key (utilisateur_id) references Utilisateur(id) on delete cascade on update cascade,
    constraint fk_Droit_Utilisation_objet foreign key (objet_id) references Objet(id) on delete cascade on update cascade
);