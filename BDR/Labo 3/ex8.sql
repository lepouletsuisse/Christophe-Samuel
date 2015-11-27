USE sakila;

SELECT DISTINCT
	c.customer_id, 
    c.first_name,
    c.last_name
FROM (SELECT DISTINCT
			 customer.customer_id, 
			 customer.first_name,
			 customer.last_name,
             film.title
		FROM 
		customer
		INNER JOIN rental
			ON customer.customer_id = rental.customer_id
		INNER JOIN inventory
			ON rental.inventory_id = inventory.inventory_id
		INNER JOIN film
			ON inventory.film_id = film.film_id
		WHERE film.film_id 
		IN (SELECT DISTINCT film_id 
			FROM actor
			INNER JOIN film_actor
				ON actor.actor_id = film_actor.actor_id
			WHERE actor.first_name = 'EMILY'
			AND actor.last_name = 'DEE'
		)
	 ) AS c
GROUP BY c.customer_id
HAVING COUNT(c.customer_id) = (
	SELECT COUNT(*) 
		FROM (SELECT DISTINCT film_id 
				FROM actor
				INNER JOIN film_actor
					ON actor.actor_id = film_actor.actor_id
				WHERE actor.first_name = 'EMILY'
				AND actor.last_name = 'DEE'
			 ) AS film2
	  );
                 