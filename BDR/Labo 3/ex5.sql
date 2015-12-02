USE sakila;
SELECT DISTINCT
	film.film_id, 
	film.title, 
	language.name AS 'langue'
FROM film
JOIN language 
    ON language.language_id = film.language_id
JOIN film_actor
	ON film_actor.film_id = film.film_id
JOIN actor
	ON actor.actor_id = film_actor.actor_id
WHERE actor.first_name = 'alan'
	OR actor.first_name = 'ben'
ORDER BY film.film_id DESC;