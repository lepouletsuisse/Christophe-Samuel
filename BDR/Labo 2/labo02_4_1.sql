use company;

delete from employee where Ssn = '333445555';

-- Refuse car si il est delete, le Super_ssn d'un autre employée pointera vers 
-- un employée qui n'existe pas

ALTER table employee drop employee_ibfk_1;
alter table employee add foreign key (Super_ssn) references employee (Ssn) ON DELETE set null;

