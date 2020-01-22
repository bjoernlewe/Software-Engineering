
--To read Sql Statements:
--.read C:/Users/Bjoern_Lewe/Software-Engineering/Project_project/Sql/projektverwaltung.sql

DROP TABLE verwaltung;
DROP TABLE studentVerwaltung;
DROP TABLE ansprechVerwaltung;
DROP TABLE student;
DROP TABLE gruppe;
DROP TABLE projekt;
DROP TABLE organisation;
DROP TABLE ansprechpartner;


CREATE TABLE verwaltung (verwaltungID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, studentID INTEGER, ansprechID INTEGER);
CREATE TABLE studentVerwaltung (sVerwaltungID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, verwaltungID INTEGER, vorname varchar(64) NOT NULL, nachname varchar(64) NOT NULL, passwort varchar(64) NOT NULL);
CREATE TABLE ansprechVerwaltung (aVerwaltungID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, verwaltungID INTEGER, vorname varchar(64) NOT NULL, nachname varchar(64) NOT NULL, passwort varchar(64) NOT NULL);


CREATE TABLE student (studentID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,gruID INTEGER, vorname varchar(64), nachname varchar(64));
CREATE TABLE gruppe (gruID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,proID INTEGER);
CREATE TABLE projekt (proID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, orgID INTEGER, gruID INTEGER, dozentID INTEGER, proName varchar(255),proBesc varchar(255),proHin varchar(255), proStatus INTEGER CHECK(proStatus >= 0 and proStatus < 3));
CREATE TABLE organisation (orgID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,proID INTEGER,ansID INTEGER, orgName varchar(255));
CREATE TABLE ansprechpartner (ansID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,orgID INTEGER, vorname varchar(64), nachname varchar(64));

--INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (1,1,'Max','Mustermann');
--INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (2,1,'Thomas','Erleuchtung');
--INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (3,2,'Paul','Invalid');
--INSERT INTO gruppe (gruID,proID) VALUES (NULL,1);
--INSERT INTO projekt (proID,orgID,gruID,proName,proBesc,proHin) VALUES (1,1,1,'Vertikaler Test', 'Test der Projektverwaltung','Um das Blatt 10 testiert zu bekommen');
INSERT INTO organisation (orgID,proID,ansID,orgName) VALUES (1,1,1,'FH Suedwestfalen');
INSERT INTO organisation (orgID,proID,ansID,orgName) VALUES (2,2,2,'Schlueter');
INSERT INTO ansprechpartner (ansID,orgID,vorname,nachname) VALUES (1,1,'Tobi','Tester');
INSERT INTO ansprechpartner (ansID,orgID,vorname,nachname) VALUES (2,1,'Max','Mister');
INSERT INTO ansprechpartner (ansID,orgID,vorname,nachname) VALUES (3,2,'Mr.','World');

--INSERT INTO student (studentID,gruID,vorname,nachname) VALUES (4,2,'Terry','Terrace')
--ON CONFLICT(studentID) DO UPDATE SET
--gruID = excluded.gruID,
--vorname = excluded.vorname,
--nachname = excluded.nachname
--WHERE studentID = excluded.studentID;

--INSERT INTO gruppe (gruID,proID) VALUES (1, 2)
--ON CONFLICT(gruID) DO UPDATE SET
--proID = excluded.proID
--WHERE gruID = excluded.gruID;

--INSERT INTO projekt (proID,orgID,gruID,proName,proBesc,proHin,proStatus)
--VALUES (2,2,2,'Testen','UPSERTTest','UPSERT testen',1)
--ON CONFLICT(proID) DO UPDATE SET
--orgID = excluded.orgID,
--gruID = excluded.gruID,
--proName = excluded.proName,
--proBesc = excluded.proBesc,
--proHin = excluded.proHin,
--proStatus = excluded.proStatus
--WHERE proID = excluded.proID;

INSERT INTO ansprechpartner (ansID,orgID,vorname,nachname)
VALUES (4,2,'Bjoern','Lewe')
ON CONFLICT(ansID) DO UPDATE SET
orgID = excluded.orgID,
vorname = excluded.vorname,
nachname = excluded.nachname
WHERE ansID = excluded.ansID;

--INSERT INTO organisation (orgID,proID,ansID,orgName)
--VALUES (':orgID',':proID',':ansID',':orgID')
--ON CONFLICT(orgID) DO UPDATE SET
--proID = excluded.proID,
--ansID = excluded.ansID,
--orgName = excluded.orgName
--WHERE orgID = excluded.orgID;

INSERT INTO verwaltung (verwaltungID,studentID,ansprechID)
VALUES (NULL,1,0)
ON CONFLICT(verwaltungID) DO UPDATE SET
studentID = excluded.studentID,
ansprechID = excluded.ansprechID
WHERE verwaltungID = excluded.verwaltungID;

INSERT INTO verwaltung (verwaltungID,studentID,ansprechID)
VALUES (NULL,2,0)
ON CONFLICT(verwaltungID) DO UPDATE SET
studentID = excluded.studentID,
ansprechID = excluded.ansprechID
WHERE verwaltungID = excluded.verwaltungID;

INSERT INTO verwaltung (verwaltungID,studentID,ansprechID)
VALUES (NULL,0,1)
ON CONFLICT(verwaltungID) DO UPDATE SET
studentID = excluded.studentID,
ansprechID = excluded.ansprechID
WHERE verwaltungID = excluded.verwaltungID;

INSERT INTO studentVerwaltung (sVerwaltungID,verwaltungID,vorname,nachname,passwort)
VALUES (NULL,1,'Bjoern','Lewe','Test')
ON CONFLICT(sVerwaltungID) DO UPDATE SET
verwaltungID = excluded.verwaltungID,
vorname = excluded.vorname,
nachname = excluded.nachname,
passwort = excluded.passwort
WHERE sVerwaltungID = excluded.sVerwaltungID;

INSERT INTO studentVerwaltung (sVerwaltungID,verwaltungID,vorname,nachname,passwort)
VALUES (NULL,2,'Franz','Tester','Test')
ON CONFLICT(sVerwaltungID) DO UPDATE SET
verwaltungID = excluded.verwaltungID,
vorname = excluded.vorname,
nachname = excluded.nachname,
passwort = excluded.passwort
WHERE sVerwaltungID = excluded.sVerwaltungID;

INSERT INTO ansprechVerwaltung (aVerwaltungID,verwaltungID,vorname,nachname,passwort)
VALUES (NULL,3,'Mr.','Dozent','admin')
ON CONFLICT(aVerwaltungID) DO UPDATE SET
verwaltungID = excluded.verwaltungID,
vorname = excluded.vorname,
nachname = excluded.nachname,
passwort = excluded.passwort
WHERE aVerwaltungID = excluded.aVerwaltungID;
