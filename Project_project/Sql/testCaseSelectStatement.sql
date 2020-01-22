
--To read Sql Statement:
--.read C:/Users/Bjoern_Lewe/Software-Engineering/Project_project/Sql/testCaseSelectStatement.sql

--.dump student
--.dump gruppe
--.dump projekt
--.dump organisation
--.dump ansprechpartner



--SELECT student.vorname,student.nachname, projekt.proName, projekt.proBesc,
--projekt.proHin,projekt.proStatus,organisation.orgName, ansprechpartner.vorname, ansprechpartner.nachname,
--ansprechVerwaltung.vorname, ansprechVerwaltung.nachname
--FROM student
--INNER JOIN gruppe USING(gruID)
--INNER JOIN projekt USING(proID)
--INNER JOIN organisation USING(orgID)
--INNER JOIN ansprechpartner USING(ansID)
--INNER JOIN ansprechVerwaltung ON ansprechVerwaltung.aVerwaltungID = projekt.dozentID
--GROUP BY projekt.proID,student.vorname, student.nachname
--HAVING projekt.proID = 3;

SELECT student.vorname,student.nachname,
projekt.proName, projekt.proBesc, projekt.proHin,projekt.proStatus,
organisation.orgName,
ansprechpartner.vorname, ansprechpartner.nachname,
ansprechVerwaltung.vorname, ansprechVerwaltung.nachname
FROM student
INNER JOIN gruppe USING(gruID)
INNER JOIN projekt USING(proID)
INNER JOIN organisation USING(orgID)
INNER JOIN ansprechpartner USING(ansID)
INNER JOIN ansprechVerwaltung ON ansprechVerwaltung.aVerwaltungID = projekt.dozentID
WHERE projekt.proID = 1;

--SELECT projekt.proID FROM student
--INNER JOIN gruppe USING (gruID)
--INNER JOIN projekt USING (proID)
--INNER JOIN studentVerwaltung
--ON student.vorname = studentVerwaltung.vorname
--AND student.nachname = studentVerwaltung.nachname
--WHERE studentVerwaltung.sVerwaltungID = 1;

--SELECT projekt.proID FROM projekt
--INNER JOIN ansprechVerwaltung
--ON ansprechVerwaltung.aVerwaltungID = projekt.dozentID
--WHERE ansprechVerwaltung.aVerwaltungID = 1;
