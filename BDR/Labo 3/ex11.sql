use sakila;

select
	film.film_id as 'id_min',
    film.title as 'titre_min',
	film.length as 'durée_min'
from film
where length = (
	select 
		min(length)
    from film)