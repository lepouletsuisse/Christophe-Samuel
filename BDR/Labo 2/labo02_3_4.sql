use company;

update employee set Dno = 7 where Ssn = '999887777';

-- Le programme refuse car Dno est une clé étrangère qui appartient
-- à la table department et est donc lié à Dnumber. Il est donc
-- pas possible de la mettre à jour car le 7 n'est aucun de nombre de department

delete from employee where Ssn = '999887777';

-- Le programme refuse car c'est une parent row de works_on

insert into works_on value('123456789', 3, 10);

-- Marche

insert into works_on value('123456789', 5, 10);

-- Le programme refuse car le projet 5 existe pas et donc il 
-- ne peut pas faire la liaison de la clé

delete from department where Dnumber = 5;

-- Le programme refuse car le departement 5 est utilisé comme
-- clé dans une autre table

insert into project value('Tera Data', 4, 1, 5);

-- Marche