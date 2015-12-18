use sakila;

select 
	prénom,
    nom,
    id,
    max(nombre_locations) as nombre_locations
from vue_ex9
limit 20;