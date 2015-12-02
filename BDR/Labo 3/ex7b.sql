USE sakila;

SELECT DISTINCT
	last_name, 
    first_name
FROM actor, film_actor, film_category
WHERE actor.actor_id = film_actor.actor_id
	AND film_actor.film_id = film_category.film_id
	AND film_category.category_id = 1
    AND first_name LIKE 'B%' 
	OR last_name LIKE 'A%';
