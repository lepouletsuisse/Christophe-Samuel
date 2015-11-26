use sakila;
select
	actor.actor_id,
    count(film.film_id) as 'nombre_films'
from actor
	inner join film_actor
		on actor.actor_id = film_actor.actor_id
	inner join film
		on film_actor.film_id = film.film_id
group by actor_id
having nombre_films > 35