use sakila;

drop view if exists vue_ex7;
create view vue_ex7
as 
	select 
		email,
		film.title as 'titre',
        datediff(NOW(), rental.rental_date + interval film.rental_duration day) as 'jours_retard'
	from rental
    inner join customer
		on rental.customer_id = customer.customer_id
    inner join inventory
		on rental.inventory_id = inventory.inventory_id
	inner join film
		on inventory.film_id = film.film_id
	where rental.return_date is null
    having jours_retard > 0;
    
    