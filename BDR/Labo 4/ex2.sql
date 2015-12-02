use sakila;

CREATE TABLE staff_creation_log (
  username varchar(16) NOT NULL,
  when_created TIMESTAMP NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=utf8;
