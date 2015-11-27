USE sakila;

SELECT DISTINCT
	c1.customer_id AS 'customer1_id',
    c1.first_name AS 'customer1_first_name',
    c1.last_name AS 'customer1_last_name',
    c2.customer_id AS 'customer2_id',
    c2.first_name AS 'customer2_first_name',
    c2.last_name AS 'customer2_last_name'
FROM customer AS c1
		INNER JOIN rental AS r1
			ON c1.customer_id = r1.customer_id
		INNER JOIN inventory AS i1
			ON r1.inventory_id = i1.inventory_id
		INNER JOIN inventory AS i2
			ON i1.film_id = i2.film_id
		INNER JOIN rental AS r2
			ON i2.inventory_id = r2.inventory_id
		INNER JOIN customer AS c2
			ON r2.customer_id = c2.customer_id
WHERE c1.customer_id > c2.customer_id;
        
        
        
        
        
        