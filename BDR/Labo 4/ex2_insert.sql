use sakila;

insert into staff(first_name, last_name, address_id, email, store_id, active, username, last_update) 
values ("Jean", "Dupond", 5, "jean.dupond@gmail.com", 3, 1, "JDup", NOW());