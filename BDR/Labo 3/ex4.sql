USE sakila;
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