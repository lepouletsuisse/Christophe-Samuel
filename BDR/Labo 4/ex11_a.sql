use sakila;

drop function if exists func_ex11;
delimiter //
create function func_ex11 (id_store int)
returns int
begin
declare nombre int;
select
	count(*)
into nombre
from (
	select distinct
		film_id
	from 
		inventory
	where
		store_id = id_store
		) as a;
return nombre;
end; //

delimiter ;