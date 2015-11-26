use sakila;
select
	film.title as 'titre',
    count(film_actor.actor_id) as nombre_acteurs
from film
	inner join film_actor
		on film.film_id = film_actor.film_id
	inner join film_category
		on film.film_id = film_category.film_id
	inner join category
		on film_category.category_id = category.category_id
	where category.name = 'Music'
group by title
order by nombre_acteurs desc;

		