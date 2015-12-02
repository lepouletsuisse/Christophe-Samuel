use sakila;

DROP TRIGGER IF EXISTS trigEx1;
DELIMITER $$
create trigger trigEx1
before insert on payment
for each row
begin
	set
		NEW.amount = NEW.amount * 1.08,
		NEW.last_update = NOW();
end; $$

DELIMITER ;