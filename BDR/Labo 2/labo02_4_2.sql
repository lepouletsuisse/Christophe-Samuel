use company;

-- update department set Dnumber = 9 where Dnumber = 1;

ALTER table employee drop foreign key employee_ibfk_2;
alter table employee add foreign key (Dno) references department (Dnumber) ON UPDATE cascade;

ALTER table dept_locations drop foreign key dept_locations_ibfk_2;
alter table dept_locations add foreign key (Dnumber) references department (Dnumber) ON UPDATE cascade;

ALTER table project drop foreign key project_ibfk_2;
alter table project add foreign key (Dnum) references department (Dnumber) ON UPDATE cascade;

update department set Dnumber = 9 where Dnumber = 1;
