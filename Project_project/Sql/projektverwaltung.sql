
--To read Sql Statements:
--.read C:/Users/Bjoern_Lewe/Software-Engineering/Project_project/Sql/projektverwaltung.sql

DROP TABLE student;
DROP TABLE gruppe;
DROP TABLE projekt;
DROP TABLE organisation;
DROP TABLE ansprechpartner;

CREATE TABLE student (studentID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,gruID INTEGER, vorname varchar(64), nachname varchar(64));
CREATE TABLE gruppe (gruID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,proID INTEGER);
CREATE TABLE projekt (proID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, orgID INTEGER, gruID INTEGER, proName varchar(255),proBesc varchar(255),proHin varchar(255), proStatus INTEGER CHECK(proStatus >= 0 and proStatus < 3));
CREATE TABLE organisation (orgID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,proID INTEGER,ansID INTEGER, orgName varchar(255));
CREATE TABLE ansprechpartner (ansID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,orgID INTEGER, vorname varchar(64), nachname varchar(64));

INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (1,1,'Max','Mustermann');
INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (2,1,'Thomas','Erleuchtung');
INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (3,2,'Paul','Invalid');
INSERT INTO gruppe (gruID,proID) VALUES (NULL,1);
INSERT INTO projekt (proID,orgID,gruID,proName,proBesc,proHin) VALUES (1,1,1,'Vertikaler Test', 'Test der Projektverwaltung','Um das Blatt 10 testiert zu bekommen');
INSERT INTO organisation (orgID,proID,ansID,orgName) VALUES (1,1,1,'FH Suedwestfalen');
INSERT INTO ansprechpartner (ansID,orgID,vorname,nachname) VALUES (1,1,'Tobi','Tester');
