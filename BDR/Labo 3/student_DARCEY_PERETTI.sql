USE sakila;

-- Exercice 01
SELECT 
	title, 
    release_year
FROM film
WHERE rating = "G" AND length > 100 AND replacement_cost = 29.99
ORDER BY title;
-- END Exercice 01

-- Exercice 02
SELECT 
	customer_id, 
    first_name, 
    last_name
FROM customer
WHERE first_name = 'Tracy' AND store_id = 1
ORDER BY customer_id DESC;
-- END Exercice 02

-- Exercice 03
SELECT 
	customer_id AS 'numéro', 
    first_name AS 'prénom', 
    last_name AS 'nom'
FROM customer
INNER JOIN address ON customer.address_id = address.address_id
WHERE active = 1 AND city_id = 321 AND store_id = 2
ORDER BY last_name;
-- END Exercice 03

-- Exercice 04
SELECT 
	country AS 'pays', 
	city AS 'ville', 
	postal_code AS 'npa'
FROM city
INNER JOIN country 
    ON city.country_id = country.country_id
JOIN address 
	ON city.city_id = address.city_id
WHERE country = 'france' 
	OR country.country_id > 50 
    AND country.country_id < 58
ORDER BY country, city, npa;
-- END Exercice 04

-- Exercice 05
SELECT DISTINCT
	film.film_id, 
	film.title, 
	language.name AS 'langue'
FROM film
JOIN language 
    ON language.language_id = film.language_id
JOIN film_actor
	ON film_actor.film_id = film.film_id
JOIN actor
	ON actor.actor_id = film_actor.actor_id
WHERE actor.first_name = 'alan'
	OR actor.first_name = 'ben'
ORDER BY film.film_id DESC;
-- END Exercice 05

-- Exercice 06
SELECT DISTINCT
	c1.customer_id AS 'customer1_id',
    c1.first_name AS 'customer1_first_name',
    c1.last_name AS 'customer1_last_name',
    c2.customer_id AS 'customer2_id',
    c2.first_name AS 'customer2_first_name',
    c2.last_name AS 'customer2_last_name'
FROM customer AS c1
		INNER JOIN rental AS r1
			ON c1.customer_id = r1.customer_id
		INNER JOIN inventory AS i1
			ON r1.inventory_id = i1.inventory_id
		INNER JOIN inventory AS i2
			ON i1.film_id = i2.film_id
		INNER JOIN rental AS r2
			ON i2.inventory_id = r2.inventory_id
		INNER JOIN customer AS c2
			ON r2.customer_id = c2.customer_id
WHERE c1.customer_id > c2.customer_id;
-- END Exercice 06

-- Exercice 07a
SELECT DISTINCT
	last_name, 
    first_name
FROM actor
INNER JOIN film_actor
	ON actor.actor_id = film_actor.actor_id
INNER JOIN film_category
	ON film_actor.film_id = film_category.film_id
INNER JOIN category
	ON film_category.category_id = category.category_id
WHERE category.name = 'Action'
	AND first_name LIKE 'B%' 
	OR last_name LIKE 'A%';
-- END Exercice 07a

-- Exercice 07b
SELECT DISTINCT
	last_name, 
    first_name
FROM actor, film_actor, film_category
WHERE actor.actor_id = film_actor.actor_id
	AND film_actor.film_id = film_category.film_id
	AND film_category.category_id = 1
    AND first_name LIKE 'B%' 
	OR last_name LIKE 'A%';
-- END Exercice 07b

-- Exercice 08
SELECT DISTINCT
	c.customer_id, 
    c.first_name,
    c.last_name
FROM (
	SELECT DISTINCT
		customer.customer_id, 
		customer.first_name,
		customer.last_name,
		film.title
	FROM 
	customer
	INNER JOIN rental
		ON customer.customer_id = rental.customer_id
	INNER JOIN inventory
		ON rental.inventory_id = inventory.inventory_id
	INNER JOIN film
		ON inventory.film_id = film.film_id
	WHERE film.film_id 
	IN (SELECT DISTINCT film_id 
		FROM actor
		INNER JOIN film_actor
			ON actor.actor_id = film_actor.actor_id
		WHERE actor.first_name = 'EMILY'
		AND actor.last_name = 'DEE'
	)
) AS c
GROUP BY c.customer_id
HAVING COUNT(c.customer_id) = (
	SELECT COUNT(*) 
		FROM (
			SELECT DISTINCT film_id 
			FROM actor
			INNER JOIN film_actor
				ON actor.actor_id = film_actor.actor_id
			WHERE actor.first_name = 'EMILY'
			AND actor.last_name = 'DEE'
		 ) AS film2
	);
-- END Exercice 08

-- Exercice 09a
SELECT
	film.title AS 'titre',
    COUNT(film_actor.actor_id) AS nombre_acteurs
FROM film
	INNER JOIN film_actor
		ON film.film_id = film_actor.film_id
	INNER JOIN film_category
		ON film.film_id = film_category.film_id
	INNER JOIN category
		ON film_category.category_id = category.category_id
	WHERE category.name = 'Music'
GROUP BY title
ORDER BY nombre_acteurs DESC;
-- END Exercice 09a

-- Exercice 09b
SELECT
	film.title AS 'titre',
	COUNT(film_actor.actor_id) AS 'nombre_acteurs'
FROM film
	INNER JOIN film_actor
		ON film.film_id = film_actor.film_id
	INNER JOIN film_category
		ON film.film_id = film_category.film_id
	INNER JOIN category
		ON film_category.category_id = category.category_id
WHERE category.name = 'Music'
GROUP BY title
HAVING nombre_acteurs > 7
ORDER BY nombre_acteurs DESC;
-- END Exercice 09b

-- Exercice 10
SELECT 
	film_category.category_id AS 'id',
	category.name AS 'nom',
    COUNT(film_id) AS 'nb_films_associés'
FROM film_category
	INNER JOIN category
		ON film_category.category_id = category.category_id

GROUP BY film_category.category_id
HAVING nb_films_associés > 60
ORDER BY nom;
-- END Exercice 10

-- Exercice 11
SELECT
	film.film_id AS 'id_min',
    film.title AS 'titre_min',
	film.length AS 'durée_min'
FROM film
WHERE length = (
	SELECT 
		MIN(length)
    FROM film);
-- END Exercice 11

-- Exercice 12
SELECT
	actor.actor_id,
    COUNT(film.film_id) AS 'nombre_films'
FROM actor
	INNER JOIN film_actor
		ON actor.actor_id = film_actor.actor_id
	INNER JOIN film
		ON film_actor.film_id = film.film_id
GROUP BY actor_id
HAVING nombre_films > 35;
-- END Exercice 12

-- Exercice 13a
SELECT
	film.film_id AS 'id',
    film.title AS 'titre'
FROM film
	INNER JOIN film_actor
		ON film.film_id = film_actor.film_id
WHERE film_actor.actor_id IN (
	SELECT actor_id
	FROM (
		SELECT
			actor.actor_id,
			COUNT(film.film_id) AS 'nombre_films'
		FROM actor
			INNER JOIN film_actor
				ON actor.actor_id = film_actor.actor_id
			INNER JOIN film
				ON film_actor.film_id = film.film_id
		GROUP BY actor_id
		HAVING nombre_films > 35
		) AS a
	)
AND film.film_id < 100
ORDER BY id;
-- END Exercice 13a

-- Exercice 13b
SELECT
	film.film_id AS 'id',
    film.title AS 'titre'
FROM film
	INNER JOIN film_actor
		ON film.film_id = film_actor.film_id
	INNER JOIN (
		SELECT
			actor.actor_id,
			COUNT(film.film_id) AS 'nombre_films'
		FROM actor
			INNER JOIN film_actor
				ON actor.actor_id = film_actor.actor_id
			INNER JOIN film
				ON film_actor.film_id = film.film_id
		GROUP BY actor_id
		HAVING nombre_films > 35
		) AS a
        ON film_actor.actor_id = a.actor_id
WHERE film.film_id < 100
ORDER BY id;
-- END Exercice 13b

-- Exercice 14
SELECT
	film.film_id,
    film.title,
    film.rental_rate AS 'prix'
FROM film
WHERE title NOT IN (
	SELECT DISTINCT
		film.title
	FROM film
		INNER JOIN inventory
			ON film.film_id = inventory.film_id
		INNER JOIN rental
			ON inventory.inventory_id = rental.inventory_id
	)
AND film.rental_rate < 2;
-- END Exercice 14

-- Exercice 15
SELECT 
	CEILING(SUM(length)/(60 * 16)) AS jours
FROM film;
-- END Exercice 15

-- Exercice 16
SELECT
	customer.customer_id AS 'id',
    customer.last_name AS 'nom',
    customer.first_name AS 'prénom',
    country.country AS 'pays',
    COUNT(customer.customer_id) AS 'nombre_films_total',
    SUM(payment.amount) AS 'total_dépense',
    AVG(payment.amount) AS 'dépense_moyenne'
    
FROM customer
	INNER JOIN payment
		ON customer.customer_id = payment.customer_id
	INNER JOIN address
		ON customer.address_id = address.address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE country.country IN ('India', 'Japan', 'Morocco')
GROUP BY customer.customer_id
HAVING dépense_moyenne > 3.4
ORDER BY pays, nom;
-- END Exercice 16

-- Exercice 17a
SELECT DISTINCT
	customer.customer_id AS 'id',
    customer.last_name AS 'nom',
    customer.first_name AS 'prénom',
    country.country AS 'pays'
FROM customer
	INNER JOIN rental
		ON customer.customer_id = rental.customer_id
	INNER JOIN address
		ON customer.address_id = address.address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE EXISTS (
	SELECT customer.customer_id
	FROM rental
	WHERE customer.customer_id = rental.customer_id
    AND rental.return_date IS NULL
    )
AND country.country = 'Japan' OR country.country = 'France'
ORDER BY pays, nom;
-- END Exercice 17a

-- Exercice 17b
SELECT DISTINCT
	customer.customer_id AS 'id',
    customer.last_name AS 'nom',
    customer.first_name AS 'prénom',
    country.country AS 'pays'
FROM customer
	INNER JOIN rental
		ON customer.customer_id = rental.customer_id
	INNER JOIN address
		ON customer.address_id = address.address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE customer.customer_id IN (
	SELECT customer.customer_id
	FROM rental
	WHERE customer.customer_id = rental.customer_id
    AND rental.return_date IS NULL
    )
AND country.country = 'Japan' OR country.country = 'France'
ORDER BY pays, nom;
-- END Exercice 17b

-- Exercice 17c
SELECT DISTINCT
	customer.customer_id AS 'id',
    customer.last_name AS 'nom',
    customer.first_name AS 'prénom',
    country.country AS 'pays'
FROM customer
	INNER JOIN rental
		ON customer.customer_id = rental.customer_id
	INNER JOIN address
		ON customer.address_id = address.address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE rental.return_date IS NULL
AND country.country = 'Japan' OR country.country = 'France'
ORDER BY pays, nom;
-- END Exercice 17c

-- Exercice 18a
SELECT
	COUNT(payment.amount)
FROM payment
WHERE payment.amount > 11;
-- END Exercice 18a

-- Exercice 18b
DELETE FROM payment
WHERE payment.amount > 11;
-- END Exercice 18b

-- Exercice 18c
SELECT
	COUNT(payment.amount)
FROM payment
WHERE payment.amount > 11;
-- END Exercice 18c

-- Exercice 19
UPDATE payment
SET amount = amount * 1.5, payment_date = NOW()
WHERE amount > 5;
-- END Exercice 19

-- Exercice 20
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
-- END Exercice 20

-- Exercice 20d
DROP PROCEDURE IF EXISTS testProcess;
DELIMITER $$
CREATE PROCEDURE testProcess()
BEGIN
SELECT *
FROM customer
	INNER JOIN address
		ON customer.address_id = address. address_id
	INNER JOIN city
		ON address.city_id = city.city_id
	INNER JOIN country
		ON city.country_id = country.country_id
WHERE first_name = "Rochat" AND last_name = "Marcel";
END$$
DELIMITER ;

CALL testProcess;
-- END Exercice 20d
