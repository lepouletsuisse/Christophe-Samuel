use sakila;

select
	film.film_id,
    film.title,
    film.rental_rate as 'prix'
from film
where title not in (
	select distinct
		film.title
	from film
		inner join inventory
			on film.film_id = inventory.inventory_id
		inner join rental
			on inventory.inventory_id = rental.inventory_id
	)
and film.rental_rate < 2.99;