USE sakila;
SELECT 
	film_category.category_id AS 'id',
	category.name AS 'nom',
    COUNT(film_id) AS 'nb_films_associés'
FROM film_category
	INNER JOIN category
		ON film_category.category_id = category.category_id

GROUP BY film_category.category_id
HAVING nb_films_associés > 60
ORDER BY nom;

