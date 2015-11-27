USE sakila;

SELECT 
	CEILING(SUM(length)/(60 * 16)) AS jours
FROM film;