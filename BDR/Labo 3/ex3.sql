USE sakila;
SELECT customer_id AS 'numéro', first_name AS 'prénom', last_name AS 'nom'
FROM customer
INNER JOIN address ON customer.address_id = address.address_id
WHERE active = 1 AND city_id = 321 AND store_id = 2
ORDER BY last_name;