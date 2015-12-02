use sakila;

insert into payment(customer_id, staff_id, rental_id, amount, payment_date) 
values (1, 1, 1, 2, now());