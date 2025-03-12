--db생성
create database mydb;
grant all privileges on mydb.* to myuser @ %;
-- grant all privileges on mydb.* to 'myuser' @'%'; /터미널에선 % 가려줘야함
use mydb;
create table Book(
    bookid integer primary key,
    bookname varchar(40),
    publicher varchar(40),
    price integer
);

-- show databases;
