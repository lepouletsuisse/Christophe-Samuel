USE sakila;

SELECT
	film.film_id AS 'id_min',
    film.title AS 'titre_min',
	film.length AS 'durée_min'
FROM film
WHERE length = (
	SELECT 
		MIN(length)
    FROM film);