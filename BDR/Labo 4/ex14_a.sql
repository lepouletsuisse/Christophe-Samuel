use sakila;

drop procedure if exists proc_ex14;
delimiter //
create procedure proc_ex14 ()
begin
update film
set last_update = NOW();
end; //

delimiter ;