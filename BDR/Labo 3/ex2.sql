use sakila;
select customer_id, first_name, last_name
from customer
where first_name = "tracy" and store_id = 1
order by customer_id desc;