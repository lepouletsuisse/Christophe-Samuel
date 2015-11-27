USE sakila;

UPDATE payment
SET amount = amount * 1.5, payment_date = NOW()
WHERE amount > 5;