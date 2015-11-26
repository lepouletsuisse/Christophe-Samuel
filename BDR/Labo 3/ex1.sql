use sakila;
SELECT title, release_year
FROM film
WHERE rating = "G" and length > 100 and replacement_cost = 29.99
order by title;
