use sakila;
DROP procedure if exists testProcess;
DELIMITER $$
CREATE procedure testProcess()
begin
select *
from customer
	inner join address
		on customer.address_id = address. address_id
	inner join city
		on address.city_id = city.city_id
	inner join country
		on city.country_id = country.country_id
where first_name = "Rochat" AND last_name = "Marcel";
end$$
DELIMITER ;

CALL testProcess;