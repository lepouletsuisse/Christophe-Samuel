use sakila;

DROP TABLE IF EXISTS customer_store_log;
DROP TRIGGER IF EXISTS trigEx4;

create table customer_store_log(
	customer_id int, 
    last_store_id int,
    register_date DATE,
    unregister_date DATE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;


DELIMITER $$
create trigger trigEx4
before update on customer
for each row 
begin
	if OLD.store_id <> NEW.store_id
    then
		insert into customer_store_log(customer_id, last_store_id, register_date, unregister_date)
		values(OLD.customer_id, OLD.store_id, OLD.last_update, now());
    end if;
end;$$

DELIMITER ;

update customer set store_id = 4 where customer_id = 1;