USE sakila;

SELECT
	COUNT(payment.amount)
FROM payment
WHERE payment.amount > 11;