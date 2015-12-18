use sakila;

drop procedure if exists proc_ex15;
delimiter //
create procedure proc_ex15 (
	in id_store int,
    out nombre_locations int,
    out nombre_exemplaires int)
begin
select 
	count(rental_id) 
into nombre_locations
from
	rental
inner join 
	inventory
on 
	rental.inventory_id = inventory.inventory_id
where 
	store_id = id_store;

select 
	count(inventory_id) 
into nombre_exemplaires
from
	inventory
where 
	store_id = id_store;

end; //

delimiter ;