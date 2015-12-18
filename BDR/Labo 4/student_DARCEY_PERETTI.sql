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
DROP TABLE IF EXISTS customer_store_log;
create table customer_store_log(
	customer_id int, 
    last_store_id int,
    register_date DATE,
    unregister_date DATE
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
-- END Exercice 04_a

-- Exercice 04_b
DROP TRIGGER IF EXISTS trigEx4;
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
-- END Exercice 04_b

-- Exercice 04_update
update customer set store_id = 4 where customer_id = 1;
-- END Exercice 04_update

-- Exercice 04_affichage
select *
from customer_store_log
where customer_id = 1;
-- END Exercice 04_affichage

-- Exercice 05
set global event_scheduler = ON;

drop event if exists delete_row;
create event delete_row on schedule every 1 minute
on completion preserve
do
	delete from customer_store_log 
		where customer_id in (
			select 
				customer_id 
			from (
				select 
					customer_id 
				from customer_store_log
				group by customer_id
				having 
					count(customer_id) > 1 
				and 
					max(unregister_date) < now() - interval 1 year
			) as tab1
		);
-- END Exercice 05

-- Exercice 06_a
drop view if exists vue_ex6;
create view vue_ex6
as 
	select 
		phone,
		address
	from staff
    inner join address
    on staff.address_id = address.address_id;
-- END Exercice 06_a

-- Exercice 06_a_affichage
select * 
from vue_ex6
limit 20;
-- END Exercice 06_a_affichage

-- Exercice 06_b
-- Oui Franklin pourra mettre à jour la base de donnée à travers cette vue car elle 
-- ne contient aucune des catégories bloquant les vues updatables :
-- pas de fonction d'aggregation, ni de distinct, ni de group by, ni de having, union,
-- sous-requête dans un select, sous-requête dans un where, etc..
update vue_ex6 set phone = '4' where phone = '14033335568';
-- END Exercice 06_b

-- Exercice 06_b_affichage
select 
	address,
	phone
from address
where address_id = 3;
-- END Exercice 06_b_affichage

-- Exercice 07
drop view if exists vue_ex7;
create view vue_ex7
as 
	select 
		email,
		film.title as 'titre',
        datediff(NOW(), rental.rental_date + interval film.rental_duration day) as 'jours_retard'
	from rental
    inner join customer
		on rental.customer_id = customer.customer_id
    inner join inventory
		on rental.inventory_id = inventory.inventory_id
	inner join film
		on inventory.film_id = film.film_id
	where rental.return_date is null
    having jours_retard > 0;
-- END Exercice 07

-- Exercice 07_affichage
select * 
from vue_ex7
limit 20;
-- END Exercice 07_affichage

-- Exercice 08
select * 
from vue_ex7
where jours_retard > 3
limit 20;
-- END Exercice 08

-- Exercice 09_a
drop view if exists vue_ex9;
create view vue_ex9
as 
	select 
		customer.first_name as 'prénom',
        customer.last_name as 'nom',
        customer.customer_id as 'id',
        count(*) as 'nombre_locations'
	from rental
    inner join customer
		on rental.customer_id = customer.customer_id
	group by customer.customer_id;
-- END Exercice 09_a

-- Exercice 09_a_affichage
select * 
from vue_ex9
limit 20;
-- END Exercice 09_a_affichage

-- Exercice 09_b
select 
	prénom,
    nom,
    id,
    max(nombre_locations) as nombre_locations
from vue_ex9
limit 20;
-- END Exercice 09_b

-- Exercice 10_a
drop view if exists vue_ex10;
create view vue_ex10
as 
	select 
		DATE(rental_date) as jour_location,
        count(*) as nombre
	from rental
    group by jour_location;
-- END Exercice 10_a

-- Exercice 10_a_affichage
select * 
from vue_ex10
limit 20;
-- END Exercice 10_a_affichage

-- Exercice 10_b
select * 
from vue_ex10
where jour_location = "2005-08-01";
-- END Exercice 10_b

-- Exercice 11_a
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
-- END Exercice 11_a

-- Exercice 11_b
select 
	func_ex11(1) as nombre_films_store_1,
	func_ex11(2) as nombre_films_store_2;
-- END Exercice 11_b

-- Exercice 12_a
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
-- END Exercice 12_a

-- Exercice 12_b
select 
	func_ex12(1) as nombre_clients_store_1,
	func_ex12(2) as nombre_clients_store_2;
-- END Exercice 12_b

-- Exercice 13_a
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
-- END Exercice 13_a

-- Exercice 13_b
select 
	func_ex13(1) as revenu_total_store_1,
	func_ex13(2) as revenu_total_store_2;
-- END Exercice 13_b

-- Exercice 14_a
drop procedure if exists proc_ex14;
delimiter //
create procedure proc_ex14 ()
begin
update film
set last_update = NOW();
end; //

delimiter ;
-- END Exercice 14_a

-- Exercice 14_b
call proc_ex14();

select 
	film_id,
    title,
	last_update
from film
limit 20;
-- END Exercice 14_b

-- Exercice 15_a
drop procedure if exists proc_ex15;
delimiter //
create procedure proc_ex15 (
	in id_store int,
    out nombre_locations int,
    out nombre_exemplaires int)
begin
select 
	count(rental_id) 
into nombre_locations
from
	rental
inner join 
	inventory
on 
	rental.inventory_id = inventory.inventory_id
where 
	store_id = id_store;

select 
	count(inventory_id) 
into nombre_exemplaires
from
	inventory
where 
	store_id = id_store;

end; //

delimiter ;
-- END Exercice 15_a

-- Exercice 15_b
call proc_ex15(1,@nombre_locations, @nombre_exemplaires);
select
	@nombre_locations,
    @nombre_exemplaires;
-- END Exercice 15_b
