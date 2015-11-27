USE sakila;

SELECT DISTINCT
	customer.customer_id AS 'id',
    customer.last_name AS 'nom',
    customer.first_name AS 'prénom',
    country.country AS 'pays'
FROM customer
	INNER JOIN rental
		ON customer.customer_id = rental.customer_id
	INNER JOIN address
		ON customer.address_id = address.address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE EXISTS (
	SELECT customer.customer_id
	FROM rental
	WHERE customer.customer_id = rental.customer_id
    AND rental.return_date IS NULL
    )
AND country.country = 'Japan' OR country.country = 'France'
ORDER BY pays, nom;
