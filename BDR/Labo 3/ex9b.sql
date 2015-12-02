USE sakila;
SELECT
	film.title AS 'titre',
	COUNT(film_actor.actor_id) AS 'nombre_acteurs'
FROM film
	INNER JOIN film_actor
		ON film.film_id = film_actor.film_id
	INNER JOIN film_category
		ON film.film_id = film_category.film_id
	INNER JOIN category
		ON film_category.category_id = category.category_id
WHERE category.name = 'Music'
GROUP BY title
HAVING nombre_acteurs > 7
ORDER BY nombre_acteurs DESC;


		