use sakila;

select distinct
	c.customer_id, 
    c.first_name,
    c.last_name
from (select distinct
			 customer.customer_id, 
			 customer.first_name,
			 customer.last_name,
             film.title
		from 
		customer
		inner join rental
			on customer.customer_id = rental.customer_id
		inner join inventory
			on rental.inventory_id = inventory.inventory_id
		inner join film
			on inventory.film_id = film.film_id
		where film.film_id 
		in (select distinct film_id 
			from actor
			inner join film_actor
				on actor.actor_id = film_actor.actor_id
			where actor.first_name = 'EMILY'
			and actor.last_name = 'DEE'
		)
	 ) as c

group by c.customer_id
having count(c.customer_id) = (select count(*) 
								from (select distinct film_id 
										from actor
										inner join film_actor
											on actor.actor_id = film_actor.actor_id
										where actor.first_name = 'EMILY'
										and actor.last_name = 'DEE'
									 ) as film2
							  )
                 