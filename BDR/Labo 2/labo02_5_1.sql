use company;

delete from employee where Ssn = '333445555';

-- Refuse car si il est delete, le Super_ssn d'un autre employée pointera vers 
-- un employée qui n'existe pas

ALTER table employee drop foreign key employee_ibfk_1;
alter table employee add foreign key (Super_ssn) references employee (Ssn) ON DELETE set null;

-- Ne marche pas en soit mais si on change le Msg_ssn et on permet le NULL, alors c'est possible.

alter table department drop foreign key department_ibfk_1;
alter table department add foreign key (Mgr_ssn) references employee (Ssn) ON DELETE set null;

-- Supprime en cascade les ligne accorder a cette employee

alter table works_on drop foreign key works_on_ibfk_1;
alter table works_on add foreign key (Essn) references employee (Ssn) on delete cascade;

alter table dependent drop foreign key dependent_ibfk_1;
alter table dependent add foreign key (Essn) references employee (Ssn) on delete cascade;

