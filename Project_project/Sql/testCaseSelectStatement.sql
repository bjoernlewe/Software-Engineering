
--To read Sql Statement:
--.read C:/Users/Bjoern_Lewe/Software-Engineering/Project_project/Sql/testCaseSelectStatement.sql

--.dump student
--.dump gruppe
--.dump projekt
--.dump organisation
--.dump ansprechpartner

SELECT * FROM student
NATURAL JOIN gruppe
NATURAL JOIN projekt
NATURAL JOIN organisation
INNER JOIN ansprechpartner ON organisation.orgID = ansprechpartner.orgID;
