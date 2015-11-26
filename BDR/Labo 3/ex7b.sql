use sakila;

select distinct
	last_name, 
    first_name
from actor, film_actor, film_category, category
where actor.actor_id = film_actor.actor_id
	and film_actor.film_id = film_category.film_id
	and film_category.category_id = category.category_id
	and category.name = 'Action'
	-- and film_category.category_id = 1
    and first_name Like 'B%' 
	or last_name like 'A%';
