use sakila;

select
	customer.customer_id as 'id',
    customer.last_name as 'nom',
    customer.first_name as 'prénom',
    country.country as 'pays',
    count(customer.customer_id) as 'nombre_films_total',
    sum(payment.amount) as 'total_dépense',
    avg(payment.amount) as 'dépense_moyenne'
    
from customer
	inner join payment
		on customer.customer_id = payment.customer_id
	inner join address
		on customer.address_id = address.address_id
	inner join city
		on address.city_id = city.city_id
	inner join country
		on city.country_id = country.country_id
where country.country in ('India', 'Japan', 'Morocco')
group by customer.customer_id
having dépense_moyenne > 3.4
order by pays, nom;
