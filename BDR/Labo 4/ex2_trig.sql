use sakila;

DROP TRIGGER IF EXISTS trigEx2;
DELIMITER $$
create trigger trigEx2
after insert on staff
for each row
begin
	insert into staff_creation_log (username, when_created)
	values (
		NEW.username,
		NEW.last_update
        );
end; $$

DELIMITER ;