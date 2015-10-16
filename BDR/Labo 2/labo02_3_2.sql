
use company;

-- --------------------------------------------------------

--
-- Change from the exercice
--

INSERT INTO works_on VALUES('123456789', 3, 10);
INSERT INTO works_on VALUES('123456789', 5, 10);

--
-- Nous constatons que ces 2 datas ont bien étés ajouter 
-- dans la base de donnée
-- 

DELETE FROM department WHERE Dnumber = 5;

-- 
-- Nous constatons a présent que le departement 5 a bien été
-- supprimé de la table department mais que la table works_on
-- n'a pas été mis à jour et donc que une entrée de cette table
-- pointe vers un departement qui n'existe pas.
-- 