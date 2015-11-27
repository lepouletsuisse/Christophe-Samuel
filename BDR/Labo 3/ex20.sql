USE sakila;

-- M. Marcel Rochat 
-- Adresse  : Rue du centre, 1260 Nyon 
-- Pays  :  Suisse / Switzerland 
-- Tél.  : 022/360.00.00 
-- E-mail : mr@bluewin.ch 
-- Rattaché au magasin N°1. 

DROP PROCEDURE IF EXISTS createMarcelRochat;

DELIMITER $$
CREATE PROCEDURE createMarcelRochat()
BEGIN
START TRANSACTION;
	IF EXISTS (
		SELECT country FROM country 
		WHERE country = "Switzerland") 
		THEN
			UPDATE country SET last_update = NOW()
				WHERE country = "Switzerland";
		ELSE 
			INSERT INTO country(country, last_update)
				VALUES("Switzerland", NOW());
	END IF;
    
    SELECT @country_id := country_id FROM country 
				WHERE country = "Switzerland";
                
    IF EXISTS (
		SELECT city FROM city
		WHERE city = "Nyon") 
		THEN
			UPDATE city SET last_update = NOW()
				WHERE city = "Nyon";
		ELSE 
			INSERT INTO city(city, country_id, last_update)
				VALUES("Nyon", @country_id, NOW());
	END IF;
    
    SELECT 
		@city_id :=city_id 
	FROM city
		WHERE city = "Nyon";

    IF EXISTS (
		SELECT address FROM address
		WHERE address = "Rue du centre") 
		THEN
			UPDATE address SET last_update = NOW()
				WHERE address = "Rue du centre";
		ELSE 
			INSERT INTO address(address, district, city_id, postal_code, phone, last_update)
				VALUES("Rue du centre", "Nyon", @city_id, "1260", "022/360.00.00", NOW());
	END IF;
    
    SELECT 
		@address_id := address_id FROM address
		WHERE address = "Rue du centre";
                
	IF EXISTS (
		SELECT customer_id FROM customer
		WHERE first_name = "Rochat" AND last_name = "Marcel") 
		THEN
			UPDATE customer SET last_update = NOW()
				WHERE first_name = "Rochat" AND last_name = "Marcel";
		ELSE 
			INSERT INTO customer(store_id, first_name, last_name, email, address_id, active, create_date, last_update)
				VALUES(1, "Rochat", "Marcel", "mr@bluewin.ch", @address_id, TRUE, NOW(), NOW());
	END IF;
COMMIT;
END$$
DELIMITER ;

CALL createMarcelRochat;
