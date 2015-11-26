use sakila;

select distinct
	last_name, 
    first_name
from actor
inner join film_actor
	on actor.actor_id = film_actor.actor_id
inner join film_category
	on film_actor.film_id = film_category.film_id
inner join category
	on film_category.category_id = category.category_id
where category.name = 'Action'
	and first_name Like 'B%' 
	or last_name like 'A%'
