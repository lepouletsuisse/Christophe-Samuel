USE sakila;
SELECT title, release_year
FROM film
WHERE rating = "G" AND length > 100 AND replacement_cost = 29.99
ORDER BY title;
