use sakila;

select distinct
	customer.customer_id as 'id',
    customer.last_name as 'nom',
    customer.first_name as 'prénom',
    country.country as 'pays'
from customer
	inner join rental
		on customer.customer_id = rental.customer_id
	inner join address
		on customer.address_id = address.address_id
	inner join city
		on address.city_id = city.city_id
	inner join country
		on city.country_id = country.country_id
where customer.customer_id in (
	select customer.customer_id
	from rental
	where customer.customer_id = rental.customer_id
    and rental.return_date is null
    )
and country.country = 'Japan' or country.country = 'France'
order by pays, nom;
