use sakila;


DROP TRIGGER IF EXISTS trigEx3;
DELIMITER $$
create trigger trigEx3
before insert on staff
for each row
begin
	set
		NEW.email = concat(NEW.first_name, '.', New.last_name, '@sakilastaff.com');
end; $$

DELIMITER ;