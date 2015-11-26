use sakila;

select 
	ceiling(sum(length)/(60 * 16)) as jours
from film;