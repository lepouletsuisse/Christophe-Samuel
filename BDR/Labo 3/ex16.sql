USE sakila;

SELECT
	customer.customer_id AS 'id',
    customer.last_name AS 'nom',
    customer.first_name AS 'prénom',
    country.country AS 'pays',
    COUNT(customer.customer_id) AS 'nombre_films_total',
    SUM(payment.amount) AS 'total_dépense',
    AVG(payment.amount) AS 'dépense_moyenne'
    
FROM customer
	INNER JOIN payment
		ON customer.customer_id = payment.customer_id
	INNER JOIN address
		ON customer.address_id = address.address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE country.country IN ('India', 'Japan', 'Morocco')
GROUP BY customer.customer_id
HAVING dépense_moyenne > 3.4
ORDER BY pays, nom;
