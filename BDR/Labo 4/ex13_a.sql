use sakila;

drop function if exists func_ex13;
delimiter //
create function func_ex13 (id_store int)
returns double
begin
declare montant double;
select
	sum(amount)
into montant
from 
	payment
inner join 
	staff
on 
	payment.staff_id = staff.staff_id
where 
	staff.store_id = id_store;
return montant;
end; //

delimiter ;