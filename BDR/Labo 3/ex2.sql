USE sakila;
SELECT customer_id, first_name, last_name
FROM customer
WHERE first_name = "tracy" AND store_id = 1
ORDER BY customer_id DESC;