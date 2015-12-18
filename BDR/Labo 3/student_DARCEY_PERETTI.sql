USE sakila;

-- Exercice 01
drop trigger if exists payment_date;
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
-- END Exercice 01

-- Exercice 01_insert
insert into payment(customer_id, staff_id, rental_id, amount, payment_date) 
values (1, 1, 1, 1, now());
-- END Exercice 01_insert

-- Exercice 01_affichage
select 
	customer_id, 
	staff_id, 
    rental_id, 
    amount, 
    payment_date
from payment
where rental_id = 1;
-- END Exercice 01_affichage

-- Exercice 02_a
CREATE TABLE staff_creation_log (
  username varchar(16) NOT NULL,
  when_created TIMESTAMP NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
-- END Exercice 02_a

-- Exercice 02_b
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
-- END Exercice 02_b

-- Exercice 02_insert
insert into staff(first_name, last_name, address_id, email, store_id, active, username, last_update) 
values ("Jean", "Dupond", 5, "jean.dupond@gmail.com", 3, 1, "JDup", NOW());
-- END Exercice 02_insert

-- Exercice 02_affichage
select *
from staff_creation_log
where username = "JDup";
-- END Exercice 02_affichage

-- Exercice 03
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
-- END Exercice 03

-- Exercice 03_insert
insert into staff(first_name, last_name, address_id, email, store_id, active, username, last_update) 
values ("Jean", "Dupond", 5, "jean.dupond@gmail.com", 3, 1, "JDup", NOW());
-- END Exercice 03_insert

-- Exercice 03_affichage
select
	first_name,
    last_name,
    email
from staff
where username = "JDUP";
-- END Exercice 03_affichage

-- Exercice 04_a

-- END Exercice 04_a

-- Exercice 04_b

-- END Exercice 04_b

-- Exercice 04_insert

-- END Exercice 04_insert

-- Exercice 04_affichage

-- END Exercice 04_affichage

-- Exercice 05

-- END Exercice 05

-- Exercice 06_a

-- END Exercice 06_a

-- Exercice 06_b

-- END Exercice 06_b

-- Exercice 07

-- END Exercice 07

-- Exercice 08

-- END Exercice 08

-- Exercice 09_a

-- END Exercice 09_a

-- Exercice 09_b

-- END Exercice 09_b

-- Exercice 10_a

-- END Exercice 10_a

-- Exercice 10_b

-- END Exercice 10_b

-- Exercice 11_a

-- END Exercice 11_a

-- Exercice 11_b

-- END Exercice 11_b

-- Exercice 12_a

-- END Exercice 12_a

-- Exercice 12_b

-- END Exercice 12_b

-- Exercice 13_a

-- END Exercice 13_a

-- Exercice 13_b

-- END Exercice 13_b

-- Exercice 14_a

-- END Exercice 14_a

-- Exercice 14_b

-- END Exercice 14_b

-- Exercice 15_a

-- END Exercice 15_a

-- Exercice 15_b

-- END Exercice 15_b
