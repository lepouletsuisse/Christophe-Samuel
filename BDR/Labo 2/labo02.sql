CREATE DATABASE company;
USE company;
CREATE TABLE employee (
	Fname varchar(15) NOT NULL, 
	Minit char(1), 
	Lname varchar(15) NOT NULL, 
	Ssn char(9) NOT NULL, 
	BDate date, 
	Address varchar(30), 
	Sex char(1), 
	Salary decimal(10,2), 
	Super_ssn char(9), 
	Dno int(11) NOT NULL, 
	primary key (Ssn), 
	foreign key (Super_ssn) references employee (Ssn),
	foreign key (Dno) references departement (Dnumber));
    
CREATE TABLE departement (
	Dname varchar(15) NOT NULL, 
	Dnumber int(11) NOT NULL, 
	Mgr_ssn char(9) NOT NULL, 
	Mgr_Start_Date date NOT NULL, 
	primary key (Dnumber),
    foreign key (Mgr_ssn) references employee (Ssn));
	
CREATE TABLE dept_locations (
	Dnumber int(11) NOT NULL, 
	Dlocation int(11) NOT NULL, 
    primary key (Dnumber, Dlocation),
    foreign key (Dlocation) references location(Lnumber),
    foreign key (Dnumber) references departement (Dnumber));
    
CREATE TABLE project (
	Pname varchar(15) NOT NULL,
    Pnumber int(11) NOT NULL, 
    Plocation int(11), 
    Dnum int(11) NOT NULL, 
    primary key (Pnumber),
    foreign key (Plocation) references location (Lnumber),
    foreign key (Dnum) references departement (Dnumber));
    
CREATE TABLE works_on (
	Essn char(9) NOT NULL, 
    Pno int(11) NOT NULL, 
    Hours decimal(3,1) NOT NULL, 
    primary key (Essn, Pno),
    foreign key (Essn) references employee (Ssn),
    foreign key (Pno) references project (Pnumber));
    
CREATE TABLE dependent (
	Essn char(9) NOT NULL,
    Dependent_Name varchar(15) NOT NULL, 
    Sex char(1), 
    Bdate date, 
    Relationship varchar(8), 
    primary key (Essn, Dependent_Name),
    foreign key (Essn) references employee(Ssn));
    
CREATE TABLE location (
	Lnumber int(11) NOT NULL,
    Lname varchar(15) NOT NULL);
