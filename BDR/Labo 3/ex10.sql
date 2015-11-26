use sakila;
select 
	film_category.category_id as 'id',
	category.name as 'nom',
    count(film_id) as 'nb_films_associés'
from film_category
	inner join category
		on film_category.category_id = category.category_id

group by film_category.category_id
having nb_films_associés > 60
order by nom;

