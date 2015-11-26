use sakila;
select customer_id as 'numéro', first_name as 'prénom', last_name as 'nom'
from customer
inner join address on customer.address_id = address.address_id
where active = 1 and city_id = 321 and store_id = 2
order by last_name;