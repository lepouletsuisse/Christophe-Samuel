use sakila;

drop view if exists vue_ex6;
create view vue_ex6
as 
	select 
		phone,
		address
	from staff
    inner join address
    on staff.address_id = address.address_id;
    
    