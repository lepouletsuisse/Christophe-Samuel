use sakila;


DROP TRIGGER IF EXISTS trigEx3;
DELIMITER $$
create trigger trigEx3
before insert on staff
for each row
begin
	set
		NEW.amount = NEW.amount * 1.08,
		NEW.last_update = NOW();
end; $$

DELIMITER ;