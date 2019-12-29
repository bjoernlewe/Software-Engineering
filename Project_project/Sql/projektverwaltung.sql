
--To read Sql Statements:
--.read C:/Users/Bjoern_Lewe/QTProjects/Project_project/Sql/projektverwaltung.sql

--DROP TABLE student;
--DROP TABLE gruppe;
--DROP TABLE projekt;
--DROP TABLE organisation;
--DROP TABLE ansprechpartner;

CREATE TABLE student (studentID int PRIMARY KEY NOT NULL,gruID int, vorname varchar(64), nachname varchar(64));
CREATE TABLE gruppe (gruID int PRIMARY KEY NOT NULL,proID int);
CREATE TABLE projekt (proID int PRIMARY KEY NOT NULL, orgID int, gruID int, proName varchar(255), proBesc varchar(255),proHin varchar(255),proStatus int CHECK(proStatus >= 0 and proStatus <3));
CREATE TABLE organisation (orgID int PRIMARY KEY NOT NULL,proID int,ansID int, orgName varchar(255));
CREATE TABLE ansprechpartner (ansID int PRIMARY KEY NOT NULL,orgID int, vorname varchar(64), nachname varchar(64));

INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (1,1,'Max','Mustermann');
INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (2,1,'Thomas','Erleuchtung');
INSERT INTO gruppe (gruID,proID) VALUES (1,1);
INSERT INTO projekt (proID,orgID,gruID,proName,proBesc,proHin) VALUES (1,1,1,'Vertikaler Test', 'Test der Projektverwaltung','Um das Blatt 10 testiert zu bekommen');
INSERT INTO organisation (orgID,proID,ansID,orgName) VALUES (1,1,1,'FH Suedwestfalen');
INSERT INTO ansprechpartner (ansID,orgID,vorname,nachname) VALUES (1,1,'Tobi','Tester');
