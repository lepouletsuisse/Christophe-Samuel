use sakila;

drop view if exists vue_ex9;
create view vue_ex9
as 
	select 
		customer.first_name as 'prénom',
        customer.last_name as 'nom',
        customer.customer_id as 'id',
        count(*) as 'nombre_locations'
	from rental
    inner join customer
		on rental.customer_id = customer.customer_id
	group by customer.customer_id;
    
    