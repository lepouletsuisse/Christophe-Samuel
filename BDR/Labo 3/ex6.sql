USE sakila;

SELECT
	customer1.customer_id AS 'customer1_id',
    customer1.first_name AS 'customer1_first_name',
    customer1.last_name AS 'customer1_last_name',
    customer2.customer_id AS 'customer2_id',
    customer2.first_name AS 'customer2_first_name',
    customer2.last_name AS 'customer2_last_name'
from(
	SELECT c1.customer_id, inventory.film_id, c1.first_name, c1.last_name
		FROM customer as c1
		INNER JOIN rental
			ON c1.customer_id = rental.customer_id
		INNER JOIN inventory
			ON rental.inventory_id = inventory.inventory_id
    ) as customer1
inner join (
	SELECT c2.customer_id, inventory.film_id, c2.first_name, c2.last_name
		FROM customer as c2
		INNER JOIN rental
			ON c2.customer_id = rental.customer_id
		INNER JOIN inventory
			ON rental.inventory_id = inventory.inventory_id
    ) as customer2
on customer1.film_id = customer2.film_id
where customer1.customer_id > customer2.customer_id;
        
        
        
        
        
        