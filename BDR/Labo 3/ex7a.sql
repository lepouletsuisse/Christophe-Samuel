USE sakila;

SELECT DISTINCT
	last_name, 
    first_name
FROM actor
INNER JOIN film_actor
	ON actor.actor_id = film_actor.actor_id
INNER JOIN film_category
	ON film_actor.film_id = film_category.film_id
INNER JOIN category
	ON film_category.category_id = category.category_id
WHERE category.name = 'Action'
	AND first_name LIKE 'B%' 
	OR last_name LIKE 'A%';
