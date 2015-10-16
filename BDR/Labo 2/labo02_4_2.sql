use company;

alter table employee add foreign key (Super_ssn) references employee (Ssn);
alter table employee add foreign key (Dno) references department (Dnumber);

alter table department add foreign key (Mgr_ssn) references employee (Ssn);

alter table dept_locations add foreign key (Dlocation) references location (Lnumber);
alter table dept_locations add foreign key (Dnumber) references department (Dnumber);

alter table project add foreign key (Plocation) references location (Lnumber);
alter table project add foreign key (Dnum) references department (Dnumber);

alter table works_on add foreign key (Essn) references employee (Ssn);
alter table works_on add foreign key (Pno) references project (Pnumber);

alter table dependent add foreign key (Essn) references employee (Ssn);