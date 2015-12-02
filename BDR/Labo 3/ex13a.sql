USE sakila;

SELECT
	film.film_id AS 'id',
    film.title AS 'titre'
FROM film
	INNER JOIN film_actor
		ON film.film_id = film_actor.film_id
WHERE film_actor.actor_id IN (
	SELECT actor_id
	FROM (
		SELECT
			actor.actor_id,
			COUNT(film.film_id) AS 'nombre_films'
		FROM actor
			INNER JOIN film_actor
				ON actor.actor_id = film_actor.actor_id
			INNER JOIN film
				ON film_actor.film_id = film.film_id
		GROUP BY actor_id
		HAVING nombre_films > 35
		) AS a
	)
AND film.film_id < 100
ORDER BY id;