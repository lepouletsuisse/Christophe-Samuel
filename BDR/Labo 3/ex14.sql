USE sakila;

SELECT
	film.film_id,
    film.title,
    film.rental_rate AS 'prix'
FROM film
WHERE title NOT IN (
	SELECT DISTINCT
		film.title
	FROM film
		INNER JOIN inventory
			ON film.film_id = inventory.film_id
		INNER JOIN rental
			ON inventory.inventory_id = rental.inventory_id
	)
AND film.rental_rate < 2;