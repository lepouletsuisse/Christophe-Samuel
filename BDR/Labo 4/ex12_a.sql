use sakila;

drop function if exists func_ex12;
delimiter //
create function func_ex12 (id_store int)
returns int
begin
declare nombre int;
select
	count(*)
into nombre
from 
	customer
where
	store_id = id_store;
return nombre;
end; //

delimiter ;