use sakila;

drop view if exists vue_ex10;
create view vue_ex10
as 
	select 
		DATE(rental_date) as jour_location,
        count(*) as nombre
	from rental
    group by jour_location;
    