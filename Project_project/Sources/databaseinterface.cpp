#include "Headers/databaseinterface.h"

#include <QException>

DatabaseInterface::DatabaseInterface(QObject *parent) : QObject (parent)
{
        if (!createConnection ()) {
                throw QString ("Could not create a Connection");
        }
        gruppen = new QVector<Gruppe*>();
        studenten = new QVector<Student*>();
        projekte = new QVector<Projekt*>();
        ansprechpartner = new QVector<Ansprechpartner*>();
        organisationen = new QVector<Organisation*>();
        verwaltung = new QVector<Verwaltung*>();
        studentenverwaltung = new QVector<StudentVerwaltung*>();
        dozentenverwaltung = new QVector<DozentVerwaltung*>();
        index = new QModelIndex ();
        setModel (nullptr);
        setListmodel (nullptr);

        initializeDatabase ();
}

void DatabaseInterface::signIn (const QString& vorname, const QString& nachname, const QString &password, const QString &typ)
{
        if (typ == "Student") {
                StudentVerwaltung* SVerwaltung = new StudentVerwaltung (0, 0, vorname, nachname, password);
                studentenverwaltung->append (SVerwaltung);
                saveStudentenVerwaltung ();
                loadStudentenVerwaltung ();
                Verwaltung* newVer = new Verwaltung (0, getMaxID (studentenverwaltung), 0);
                verwaltung->append (newVer);
                saveVerwaltung ();
                loadVerwaltung ();
                studentenverwaltung->last ()->setForeignKey (getMaxID (verwaltung));
                saveStudentenVerwaltung ();
                loadStudentenVerwaltung ();
        }
        else if (typ == "Dozent") {
                DozentVerwaltung* AVerwaltung = new DozentVerwaltung (0, 0, vorname, nachname, password);
                dozentenverwaltung->append (AVerwaltung);
                saveAnsprechVerwaltung ();
                loadAnsprechVerwaltung ();
                Verwaltung* newVer = new Verwaltung (0, 0, getMaxID (dozentenverwaltung));
                verwaltung->append (newVer);
                saveVerwaltung ();
                loadVerwaltung ();
                dozentenverwaltung->last ()->setForeignKey (getMaxID (verwaltung));
                saveAnsprechVerwaltung ();
                loadAnsprechVerwaltung ();
        }
        else{
                throw QString ("DatabaseInterface::signIn(): no such type: " + typ);
        }
}

void DatabaseInterface::loadTables ()
{
        loadStudenten ();
        loadGruppen ();
        loadProjekte ();
        loadOrganisation ();
        loadAnsprechpartner ();
        loadVerwaltung ();
        loadStudentenVerwaltung ();
        loadAnsprechVerwaltung ();
}

void DatabaseInterface::saveTables ()
{
        saveGruppen ();
        saveStudenten ();
        saveProjekte ();
        saveOrganisation ();
        saveAnsprechpartner ();
        saveVerwaltung ();
        saveStudentenVerwaltung ();
        saveStudentenVerwaltung ();
}

void DatabaseInterface::printAll ()
{
        for (int i = 0; i < studenten->length (); i++) {
                qDebug () << "Student(studentID: " << studenten->at (i)->getPrimaryKey () << "| gruID: " << studenten->at (i)->getForeignKey () << "|" << studenten->at (i)->getVorname () << "|" << studenten->at (i)->getNachname () << ")";
        }

        for (int i = 0; i < gruppen->length (); i++) {
                qDebug () << "Gruppe(gruID: " << gruppen->at (i)->getPrimaryKey () << "| proID: " << gruppen->at (i)->getForeignKey () << ")";
        }

        for (int i = 0; i < projekte->length (); i++) {
                qDebug () << "Projekt(proID: " << projekte->at (i)->getPrimaryKey () << "| orgID: " << projekte->at (i)->getForeignOrgKey () << "| gruID: " << projekte->at (i)->getForeignGruKey () << "| dozentID: " << projekte->at (i)->getForeignDozKey () << "|" << projekte->at (i)->getProjektName () << "|" << projekte->at (i)->getBeschreibung () << "|" << projekte->at (i)->getHintergrund () << "|" << projekte->at (i)->getStatus () << ")";
        }

        for (int i = 0; i < organisationen->length (); i++) {
                qDebug () << "Organisation( orgID: " << organisationen->at (i)->getPrimaryKey () << "| ansID: " << organisationen->at (i)->getForeignAnsKey () << "| proID: " << organisationen->at (i)->getForeignProKey () << "|" << organisationen->at (i)->getOrganisationName () << ")";
        }

        for (int i = 0; i < ansprechpartner->length (); i++) {
                qDebug () << "Ansprechpartner( ansID: " << ansprechpartner->at (i)->getPrimaryKey () << "| orgID: " << ansprechpartner->at (i)->getForeignKey () << "|" << ansprechpartner->at (i)->getVorname () << "|" << ansprechpartner->at (i)->getNachname () << ")";
        }

        for (int i = 0; i < verwaltung->length (); i++) {
                qDebug () << "Verwaltung( verwaltungID: " << verwaltung->at (i)->getPrimaryKey () << "| sVerwaltungID: " << verwaltung->at (i)->getForeignStuKey () << "| aVerwaltungID: " << verwaltung->at (i)->getForeignAnsKey () << ")";
        }

        for (int i = 0; i < dozentenverwaltung->length (); i++) {
                qDebug () << "DozentVerwaltung( dozentID: " << dozentenverwaltung->at (i)->getPrimaryKey () << "| verwaltungID: " << dozentenverwaltung->at (i)->getForeignKey () << "|" << dozentenverwaltung->at (i)->getVorname () << "|" << dozentenverwaltung->at (i)->getNachname () << "|" << dozentenverwaltung->at (i)->getPassword () << ")";
        }

        for (int i = 0; i < studentenverwaltung->length (); i++) {
                qDebug () << "StudentVerwaltung( sVerwaltungID: " << studentenverwaltung->at (i)->getPrimaryKey () << "| verwaltungID: " << studentenverwaltung->at (i)->getForeignKey () << "|" << studentenverwaltung->at (i)->getVorname () << "|" << studentenverwaltung->at (i)->getNachname () << "|" << studentenverwaltung->at (i)->getPassword () << ")";
        }
        qDebug () << "========================================================";

        for (int id = 1; id <= getMaxID (projekte); id++) {
                QList<QMap<QString, QString>*>* projects = getOneProject (id);
                for (int j = 0; j < projects->length (); j++) {
                        QMapIterator<QString, QString>*iter = new QMapIterator<QString, QString>(*projects->at (j));
                        qDebug () << "";
                        while (iter->hasNext ()) {
                                auto item = iter->next ();
                                qDebug () << "(" << item.key () << ", " << item.value () << ")";
                        }
                }
        }
}

void DatabaseInterface::loadGruppen ()
{
        gruppen->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM gruppe");

        while (query.next ()) {
                Gruppe* newGroup = new Gruppe (query.value ("gruID").toInt (), query.value ("proID").toInt ());
                gruppen->append (newGroup);
        }

        gruppeOriginalSize = gruppen->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadGruppen: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadStudenten ()
{
        studenten->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM student;");

        while (query.next ()) {
                Student* newStudent = new Student (query.value ("studentID").toInt (), query.value ("vorname").toString (), query.value ("nachname").toString (), query.value ("gruID").toInt ());
                studenten->append (newStudent);
        }

        studentenOriginalSize = studenten->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadStudenten: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadProjekte ()
{
        projekte->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM projekt");


        while (query.next ()) {
                bool status = query.value ("proStatus") == 0 ? static_cast<bool>(nullptr) : query.value ("proStatus").toBool ();
                Projekt* newProject = new Projekt (query.value ("proID").toInt (), query.value ("orgID").toInt (), query.value ("gruID").toInt (), query.value ("dozentID").toInt (), query.value ("proName").toString (), query.value ("proBesc").toString (), query.value ("proHin").toString (), status);
                projekte->append (newProject);
        }

        projekteOriginalSize = projekte->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadProjekte: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadAnsprechpartner ()
{
        ansprechpartner->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM ansprechpartner");

        while (query.next ()) {
                Ansprechpartner* newAnsprech = new Ansprechpartner (query.value ("ansID").toInt (), query.value ("vorname").toString (), query.value ("nachname").toString (), query.value ("orgID").toInt ());
                ansprechpartner->append (newAnsprech);
        }

        ansprechOriginalSize = ansprechpartner->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadAnsprechpartner: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadOrganisation ()
{
        organisationen->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM organisation");

        while (query.next ()) {
                Organisation* newOrg = new Organisation (query.value ("orgID").toInt (), query.value ("proID").toInt (), query.value ("ansID").toInt (), query.value ("orgName").toString ());
                organisationen->append (newOrg);
        }

        orgOriginalSize = organisationen->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadOrganisation: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadVerwaltung ()
{
        verwaltung->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM verwaltung");

        while (query.next ()) {
                Verwaltung* newVerwaltung = new Verwaltung (query.value ("verwaltungID").toInt (), query.value ("studentID").toInt (), query.value ("ansprechID").toInt ());
                verwaltung->append (newVerwaltung);
        }

        verwaltungOriginalSize = verwaltung->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadVerwaltung: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadStudentenVerwaltung ()
{
        studentenverwaltung->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM studentVerwaltung");

        while (query.next ()) {
                StudentVerwaltung* newSVerwaltung = new StudentVerwaltung (query.value ("sVerwaltungID").toInt (), query.value ("verwaltungID").toInt (), query.value ("vorname").toString (), query.value ("nachname").toString (), query.value ("passwort").toString ());
                studentenverwaltung->append (newSVerwaltung);
        }

        stuVerwaltungOriginalSize = studentenverwaltung->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadStudentenVerwaltung: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::loadAnsprechVerwaltung ()
{
        dozentenverwaltung->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM ansprechVerwaltung");

        while (query.next ()) {
                DozentVerwaltung* newAVerwaltung = new DozentVerwaltung (query.value ("aVerwaltungID").toInt (), query.value ("verwaltungID").toInt (), query.value ("vorname").toString (), query.value ("nachname").toString (), query.value ("passwort").toString ());
                dozentenverwaltung->append (newAVerwaltung);
        }

        ansVerwaltungOriginalSize = dozentenverwaltung->length ();

        if (query.lastError ().isValid ()) {
                qDebug () << "loadAnsprechVerwaltung: " << query.lastError ();
                return;
        }
}

void DatabaseInterface::saveGruppen ()
{
        QSqlQuery query;
        QString statement = "INSERT INTO gruppe (gruID,proID)"
                            "VALUES (:gruID, :proID)"
                            "ON CONFLICT(gruID) DO UPDATE SET "
                            "proID = excluded.proID "
                            "WHERE gruID = excluded.gruID;";

        for (int i = 0; i < gruppen->length (); i++) {
                query.prepare (statement);
                query.bindValue (":gruID", gruppen->at (i)->getPrimaryKey () <= 0 ? getMaxID (gruppen) + 1 : gruppen->at (i)->getPrimaryKey ());
                query.bindValue (":proID", gruppen->at (i)->getForeignKey ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveGruppen: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveStudenten ()
{
        QSqlQuery query;

        QString statement ("INSERT INTO student (studentID,gruID,vorname,nachname)"
                           "VALUES (:studentID,:gruID,:vorname,:nachname)"
                           "ON CONFLICT(studentID) DO UPDATE SET "
                           "gruID = excluded.gruID, "
                           "vorname = excluded.vorname, "
                           "nachname = excluded.nachname "
                           "WHERE studentID = excluded.studentID;");

        for (int i = 0; i < studenten->length (); i++) {
                query.prepare (statement);
                query.bindValue (":studentID", studenten->at (i)->getPrimaryKey () <= 0 ? getMaxID (studenten) + 1 : studenten->at (i)->getPrimaryKey ());
                query.bindValue (":gruID", studenten->at (i)->getForeignKey ());
                query.bindValue (":vorname", studenten->at (i)->getVorname ());
                query.bindValue (":nachname", studenten->at (i)->getNachname ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveStudenten: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveProjekte ()
{
        QSqlQuery query;

        QString statement = "INSERT INTO projekt (proID,orgID,gruID,dozentID,proName,proBesc,proHin,proStatus)"
                            "VALUES (:proID,:orgID,:gruID,:dozentID,:proName,:proBesc,:proHin,:proStatus)"
                            "ON CONFLICT(proID) DO UPDATE SET "
                            "orgID = excluded.orgID, "
                            "gruID = excluded.gruID, "
                            "dozentID = excluded.dozentID, "
                            "proName = excluded.proName, "
                            "proBesc = excluded.proBesc, "
                            "proHin = excluded.proHin, "
                            "proStatus = excluded.proStatus "
                            "WHERE proID = excluded.proID;";

        for (int i = 0; i < projekte->length (); i++) {
                query.prepare (statement);
                query.bindValue (":proID", projekte->at (i)->getPrimaryKey () <= 0 ? getMaxID (projekte) + 1 : projekte->at (i)->getPrimaryKey ());
                query.bindValue (":orgID", projekte->at (i)->getForeignOrgKey ());
                query.bindValue (":gruID", projekte->at (i)->getForeignGruKey ());
                query.bindValue (":dozentID", projekte->at (i)->getForeignDozKey ());
                query.bindValue (":proName", projekte->at (i)->getProjektName ());
                query.bindValue (":proBesc", projekte->at (i)->getBeschreibung ());
                query.bindValue (":proHin", projekte->at (i)->getHintergrund ());
                query.bindValue (":proStatus", projekte->at (i)->getStatus ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveProjekte: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveAnsprechpartner ()
{
        QSqlQuery query;

        QString statement = "INSERT INTO ansprechpartner (ansID, orgID, vorname, nachname)"
                            "VALUES (:ansID, :orgID, :vorname, :nachname)"
                            "ON CONFLICT(ansID) DO UPDATE SET "
                            "orgID = excluded.orgID, "
                            "vorname = excluded.vorname, "
                            "nachname = excluded.nachname "
                            "WHERE ansID = excluded.ansID;";

        for (int i = 0; i < ansprechpartner->length (); i++) {
                query.prepare (statement);
//                qDebug () << ansprechpartner->at (i)->getPrimaryKey () << ansprechpartner->at (i)->getForeignKey () << ansprechpartner->at (i)->getVorname () << ansprechpartner->at (i)->getNachname ();
                query.bindValue (":ansID", ansprechpartner->at (i)->getPrimaryKey () <= 0 ? getMaxID (ansprechpartner) + 1 : ansprechpartner->at (i)->getPrimaryKey ());
                query.bindValue (":orgID", ansprechpartner->at (i)->getForeignKey ());
                query.bindValue (":vorname", ansprechpartner->at (i)->getVorname ());
                query.bindValue (":nachname", ansprechpartner->at (i)->getNachname ());
                qDebug () << query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveAnsprechpartner: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveOrganisation ()
{
        QSqlQuery query;


        QString statement = "INSERT INTO organisation (orgID,proID,ansID,orgName)"
                            "VALUES (:orgID,:proID,:ansID,:orgName)"
                            "ON CONFLICT(orgID) DO UPDATE SET "
                            "proID = excluded.proID, "
                            "ansID = excluded.ansID, "
                            "orgName = excluded.orgName "
                            "WHERE orgID = excluded.orgID;";

        for (int i = 0; i < organisationen->length (); i++) {
                query.prepare (statement);
                query.bindValue (":orgID", organisationen->at (i)->getPrimaryKey () <= 0 ? getMaxID (organisationen) + 1 : organisationen->at (i)->getPrimaryKey ());
                query.bindValue (":proID", organisationen->at (i)->getForeignProKey ());
                query.bindValue (":ansID", organisationen->at (i)->getForeignAnsKey ());
                query.bindValue (":orgName", organisationen->at (i)->getOrganisationName ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveOrganisation: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveVerwaltung ()
{
        QSqlQuery query;
        QString statement = "INSERT INTO verwaltung (verwaltungID,studentID,ansprechID)"
                            "VALUES (:verwaltungID,:studentID,:ansprechID)"
                            "ON CONFLICT(verwaltungID) DO UPDATE SET "
                            "studentID = excluded.studentID, "
                            "ansprechID = excluded.ansprechID "
                            "WHERE verwaltungID = excluded.verwaltungID;";

        for (int i = 0; i < verwaltung->length (); i++) {
                query.prepare (statement);
                query.bindValue (":verwaltungID", verwaltung->at (i)->getPrimaryKey () <= 0 ? getMaxID (verwaltung) + 1 : verwaltung->at (i)->getPrimaryKey ());
                query.bindValue (":studentID", verwaltung->at (i)->getForeignStuKey ());
                query.bindValue (":ansprechID", verwaltung->at (i)->getForeignAnsKey ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveVerwaltung: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveStudentenVerwaltung ()
{
        QSqlQuery query;
        QString statement = "INSERT INTO studentVerwaltung (sVerwaltungID,verwaltungID,vorname,nachname,passwort)"
                            "VALUES (:sVerwaltungID,:verwaltungID,:vorname,:nachname,:passwort)"
                            "ON CONFLICT(sVerwaltungID) DO UPDATE SET "
                            "verwaltungID = excluded.verwaltungID, "
                            "vorname = excluded.vorname, "
                            "nachname = excluded.nachname, "
                            "passwort = excluded.passwort "
                            "WHERE sVerwaltungID = excluded.sVerwaltungID;";

        for (int i = 0; i < studentenverwaltung->length (); i++) {
                query.prepare (statement);
                query.bindValue (":sVerwaltungID", studentenverwaltung->at (i)->getPrimaryKey () <= 0 ? getMaxID (studentenverwaltung) + 1 : studentenverwaltung->at (i)->getPrimaryKey ());
                query.bindValue (":verwaltungID", studentenverwaltung->at (i)->getForeignKey ());
                query.bindValue (":vorname", studentenverwaltung->at (i)->getVorname ());
                query.bindValue (":nachname", studentenverwaltung->at (i)->getNachname ());
                query.bindValue (":passwort", studentenverwaltung->at (i)->getPassword ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveStudentenVerwaltung: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::saveAnsprechVerwaltung ()
{
        QSqlQuery query;
        QString statement = "INSERT INTO ansprechVerwaltung (aVerwaltungID,verwaltungID,vorname,nachname,passwort)"
                            "VALUES (:aVerwaltungID,:verwaltungID,:vorname,:nachname,:passwort)"
                            "ON CONFLICT(aVerwaltungID) DO UPDATE SET "
                            "verwaltungID = excluded.verwaltungID, "
                            "vorname = excluded.vorname, "
                            "nachname = excluded.nachname, "
                            "passwort = excluded.passwort "
                            "WHERE aVerwaltungID = excluded.aVerwaltungID;";

        for (int i = 0; i < dozentenverwaltung->length (); i++) {
                query.prepare (statement);
                query.bindValue (":aVerwaltungID", dozentenverwaltung->at (i)->getPrimaryKey () <= 0 ? getMaxID (dozentenverwaltung) + 1 : dozentenverwaltung->at (i)->getPrimaryKey ());
                query.bindValue (":verwaltungID", dozentenverwaltung->at (i)->getForeignKey ());
                query.bindValue (":vorname", dozentenverwaltung->at (i)->getVorname ());
                query.bindValue (":nachname", dozentenverwaltung->at (i)->getNachname ());
                query.bindValue (":passwort", dozentenverwaltung->at (i)->getPassword ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveAnsprechverwaltung: " << i << query.lastError ();
                        return;
                }
                query.clear ();
        }
}

void DatabaseInterface::removeOrgAt (int id)
{
        QSqlQuery query;

        query.prepare ("DELETE FROM organisation WHERE orgID = :id");
        query.bindValue (":id", id);
        query.exec ();

        if (query.lastError ().isValid ()) {
                qDebug () << "removeOrgAt " << id << ": " << query.lastError ();
                return;
        }
}

void DatabaseInterface::removeAnsAt (int id)
{
        QSqlQuery query;

        query.prepare ("DELETE FROM ansprechpartner WHERE ansID = :id");
        query.bindValue (":id", id);
        query.exec ();

        if (query.lastError ().isValid ()) {
                qDebug () << "removeAnsAt " << id << ": " << query.lastError ();
                return;
        }
}

int DatabaseInterface::getMaxID (QVector<Ansprechpartner *> *tmp)
{
        Ansprechpartner* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<Student *> *tmp)
{
        Student* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<Gruppe *> *tmp)
{
        Gruppe* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<Projekt *> *tmp)
{
        Projekt* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<Organisation *> *tmp)
{
        Organisation* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<DozentVerwaltung *> *tmp)
{
        DozentVerwaltung* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<StudentVerwaltung *> *tmp)
{
        StudentVerwaltung* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

int DatabaseInterface::getMaxID (QVector<Verwaltung *> *tmp)
{
        Verwaltung* buffer = nullptr;

        for (int i = 0; i < tmp->length (); i++) {
                if (buffer == nullptr) {
                        buffer = tmp->at (i);
                }
                else{
                        if (buffer->getPrimaryKey () < tmp->at (i)->getPrimaryKey ()) {
                                buffer = tmp->at (i);
                        }
                }
        }
        int ret = 0;
        if (buffer != nullptr)
                ret = buffer->getPrimaryKey ();
        return ret;
}

QVector<DozentVerwaltung *> *DatabaseInterface::getAnsprechVerwaltung () const
{
        return dozentenverwaltung;
}

void DatabaseInterface::setAnsprechVerwaltung (QVector<DozentVerwaltung *> *value)
{
        dozentenverwaltung = value;
}

QStandardItemModel *DatabaseInterface::getModel () const
{
        return model;
}

void DatabaseInterface::setModel (QStandardItemModel *value)
{
        model = value;
        if (model == nullptr)
                model = new QStandardItemModel ();
}

QModelIndex *DatabaseInterface::getIndex () const
{
        return index;
}

void DatabaseInterface::setIndex (QModelIndex *value)
{
        index = value;
}

QStringListModel *DatabaseInterface::getListmodel () const
{
        return listmodel;
}

void DatabaseInterface::setListmodel (QStringListModel *value)
{
        listmodel = value;
        if (listmodel == nullptr)
                listmodel = new QStringListModel ();
}

QMap<int, QString> DatabaseInterface::getKEYS () const
{
        return KEYS;
}

void DatabaseInterface::setKEYS (const QMap<int, QString> &value)
{
        KEYS = value;
}

void DatabaseInterface::changeIndex (const QModelIndex &index)
{
        this->index = new QModelIndex (index);
}

QVector<StudentVerwaltung *> *DatabaseInterface::getStudentenverwaltung () const
{
        return studentenverwaltung;
}

void DatabaseInterface::setStudentenverwaltung (QVector<StudentVerwaltung *> *value)
{
        studentenverwaltung = value;
}

QVector<Verwaltung *> *DatabaseInterface::getVerwaltung () const
{
        return verwaltung;
}

void DatabaseInterface::setVerwaltung (QVector<Verwaltung *> *value)
{
        verwaltung = value;
}

QVector<Organisation *> *DatabaseInterface::getOrganisationen () const
{
        return organisationen;
}

void DatabaseInterface::setOrganisationen (QVector<Organisation *> *value)
{
        organisationen = value;
}

QVector<Ansprechpartner *> *DatabaseInterface::getAnsprechpartner () const
{
        return ansprechpartner;
}

void DatabaseInterface::setAnsprechpartner (QVector<Ansprechpartner *> *value)
{
        ansprechpartner = value;
}

QVector<Projekt *> *DatabaseInterface::getProjekte () const
{
        return projekte;
}

void DatabaseInterface::setProjekte (QVector<Projekt *> *value)
{
        projekte = value;
}

QVector<Student *> *DatabaseInterface::getStudenten () const
{
        return studenten;
}

void DatabaseInterface::setStudenten (QVector<Student *> *value)
{
        studenten = value;
}

QVector<Gruppe *> *DatabaseInterface::getGruppen () const
{
        return gruppen;
}

void DatabaseInterface::setGruppen (QVector<Gruppe *> *value)
{
        gruppen = value;
}

bool DatabaseInterface::createConnection ()
{
        if (!(db.isOpen () || db.isValid ())) {
                db = QSqlDatabase::addDatabase ("QSQLITE");
        }

        db.setDatabaseName ("projektverwaltung");
        if (!db.open ()) {
                QMessageBox::critical (nullptr, QObject::tr ("Cannot open database"),
                        QObject::tr ("Unable to establish a database connection.\n"
                                "This example needs SQLite support. Please read "
                                "the Qt SQL driver documentation for information how "
                                "to build it.\n\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
                return false;
        }

        if (db.lastError ().isValid ()) {
                qDebug () << "createConnection: " << db.lastError ();
                return false;
        }
//        qDebug () << db.commit ();
        return true;
}

void DatabaseInterface::initializeDatabase ()
{
        loadTables ();
        KEYS.insert (1, "student.name");
        KEYS.insert (2, "projekt.proStatus");
        KEYS.insert (3, "projekt.proName");
        KEYS.insert (4, "projekt.proHin");
        KEYS.insert (5, "projekt.proBesc");
        KEYS.insert (6, "organisation.orgName");
        KEYS.insert (7, "ansprechpartner.vorname");
        KEYS.insert (8, "ansprechpartner.nachname");
        KEYS.insert (9, "ansprechVerwaltung.vorname");
        KEYS.insert (10, "ansprechVerwaltung.nachname");
        //testing
        printAll ();
}

QList<int> DatabaseInterface::getProjektID (const QString &type, int id)
{
        QSqlQuery query;

        if (type == "Student") {
                query.prepare ("SELECT projekt.proID FROM student "
                        "INNER JOIN gruppe USING (gruID) "
                        "INNER JOIN projekt USING (proID) "
                        "INNER JOIN studentVerwaltung "
                        "ON student.vorname = studentVerwaltung.vorname "
                        "AND student.nachname = studentVerwaltung.nachname "
                        "WHERE studentVerwaltung.sVerwaltungID = :id;");
                query.bindValue (":id", id);
                query.exec ();
                QList<int> projects;
                while (query.next ()) {
                        projects << query.value ("projekt.proID").toInt ();
                }
                return projects;
        }
        else if (type == "Dozent") {
                query.prepare ("SELECT projekt.proID FROM projekt "
                        "INNER JOIN ansprechVerwaltung "
                        "ON ansprechVerwaltung.aVerwaltungID = projekt.dozentID "
                        "WHERE ansprechVerwaltung.aVerwaltungID = :id;");
                query.bindValue (":id", id);
                query.exec ();
                QList<int>projects;
                while (query.next ()) {
                        projects << query.value ("projekt.proID").toInt ();
                }
                return projects;
        }
        else {
                throw QString ("getProjektID(): No such type " + type);
        }
}

void DatabaseInterface::getValuesFromDatabase (QStandardItemModel* model, const QString& type, int id)
{
        QList<int> allProIDs = getProjektID (type, id);

        model->clear ();
        for (int i = 0; i < allProIDs.length (); i++) {
                QList<QMap<QString, QString>*>* projekts = getOneProject (allProIDs.at (i));
                QStringList remember;
                for (int j = 0; j < projekts->length (); j++) {
                        QMapIterator<QString, QString>* iter = new QMapIterator<QString, QString>(*projekts->at (j));
                        QString vorname;
                        QString nachname;
                        if (!(projekts->at (j)->key (this->index->data ().toString ()).isEmpty ()
                              || projekts->at (j)->key (this->index->data ().toString ()).isNull ())) {
                                while (iter->hasNext ()) {
                                        auto item = iter->next ();
                                        if (!remember.contains (item.key ())
                                            || item.key () == "student.vorname"
                                            || item.key () == "student.nachname") {
                                                if (!remember.contains (item.key ()))
                                                        remember << item.key ();
                                                if (!(item.key () == "projekt.proStatus")) {
                                                        if (!(item.key () == "student.vorname" || item.key () == "student.nachname")) {
                                                                QStandardItem* newItem = new QStandardItem (item.key () + ":\t\t" + item.value ());
                                                                model->appendRow (newItem);
                                                        }
                                                        else {
                                                                if ((item.key () == "student.vorname")) {
                                                                        vorname = item.value ();
                                                                }
                                                                else {
                                                                        nachname = item.value ();
                                                                }
                                                                if (!(nachname.isNull () || nachname.isEmpty () || vorname.isNull () || vorname.isEmpty ())) {
                                                                        QStandardItem* newItem = new QStandardItem ("student.name:\t\t" + vorname + ", " + nachname);
                                                                        model->appendRow (newItem);
                                                                }
                                                        }
                                                }
                                                else{
                                                        QString statusTxt;
                                                        if (item.value () == "0") {
                                                                statusTxt = "Abgelehnt";
                                                        }
                                                        else if (item.value () == "1") {
                                                                statusTxt = "Angenommen";
                                                        }
                                                        else{
                                                                statusTxt = "Zur Bearbeitung freigegeben";
                                                        }
                                                        QStandardItem* newItem = new QStandardItem (item.key () + ":\t\t" + statusTxt);
                                                        model->appendRow (newItem);
                                                }
                                        }
                                }
                        }
                }
        }
        model->sort (0, Qt::SortOrder::DescendingOrder);
}

void DatabaseInterface::getValuesFromDatabase (QStringListModel *model, const QString& type, int id)
{
        QStringList list;
        QList<int> allProIDs = getProjektID (type, id);

        for (int i = 0; i < allProIDs.length (); i++) {
                QList<QMap<QString, QString>*>* projekts = getOneProject (allProIDs.at (i));
                list << projekts->first ()->value ("projekt.proName");
        }
        model->setStringList (list);
}

void DatabaseInterface::getStudentComboItems (QComboBox* box, const QModelIndex* index, int id)
{
        QStringList item = index->data ().toString ().split (":");

        box->clear ();
        for (int i = 0; i < studentenverwaltung->length (); i++) {
                box->addItem (studentenverwaltung->at (i)->getVorname () + " " + studentenverwaltung->at (i)->getNachname ());
        }
        if (index->data ().toString () == "projekt.name") {
                QList<QMap<QString, QString>*>* projekt = getOneProject (id);
                qDebug () << projekt->first ()->value ("projekt.vorname") << " " << projekt->first ()->value ("projekt.nachname");
//                box->setCurrentText (projekt->first ()->value ();
        }


        qDebug () << item;
}

void DatabaseInterface::getOrgComboItems (QComboBox *box, const QModelIndex *index, int id)
{
        QStringList item = index->data ().toString ().split (":");

        box->clear ();
        for (int i = 0; i < organisationen->length (); i++) {
                box->addItem (organisationen->at (i)->getOrganisationName ());
        }
        if (this->index->row () + 1 > 0) {
                int forOrg = projekte->at (this->index->row () + 1)->getForeignOrgKey ();
                box->setCurrentIndex (forOrg - 1);
        }
}

void DatabaseInterface::getAnsprechComboItems (QComboBox *box, const QModelIndex *index, int id)
{
}

void DatabaseInterface::getView (QListView *view, const QString& type, int id)
{
        if (this->listmodel == nullptr)
                this->listmodel = new QStringListModel ();
        getValuesFromDatabase (this->listmodel, type, id);
        view->setModel (this->listmodel);
}

void DatabaseInterface::getItemView (QListView *view, const QString &type, int id)
{
        if (this->model == nullptr)
                model = new QStandardItemModel ();

        getValuesFromDatabase (this->model, type, id);
        view->setModel (this->model);
}

void DatabaseInterface::getMappedWidget (QDataWidgetMapper* mapper, QList<QWidget *> widgets, const QString &type, int id)
{
        getValuesFromDatabase (this->model, type, id);
        mapper->setModel (this->model);
        for (int i = 0; i < widgets.length (); i++) {
                if (strcmp (widgets.at (i)->metaObject ()->className (), "QComboBox") == 0) {
                        qDebug () << widgets.at (i);
                        if (widgets.at (i)->objectName () == "comboBox_1" ||
                            widgets.at (i)->objectName () == "comboBox_2" ||
                            widgets.at (i)->objectName () == "comboBox_3")
                                getStudentComboItems (static_cast<QComboBox*>(widgets.at (i)), this->index, id);
                        if (widgets.at (i)->objectName () == "orgCombo")
                                getOrgComboItems (static_cast<QComboBox*>(widgets.at (i)), this->index, id);
                }
                mapper->addMapping (widgets.at (i), i);
        }
}


QList<QMap<QString, QString>*>* DatabaseInterface::getOneProject (int id)
{
        QSqlQuery query;
        QString statement ("SELECT student.vorname,student.nachname, "
                           "projekt.proName, projekt.proBesc, projekt.proHin,projekt.proStatus, "
                           "organisation.orgName, "
                           "ansprechpartner.vorname, ansprechpartner.nachname, "
                           "ansprechVerwaltung.vorname, ansprechVerwaltung.nachname "
                           "FROM student "
                           "INNER JOIN gruppe USING(gruID) "
                           "INNER JOIN projekt USING(proID) "
                           "INNER JOIN organisation USING(orgID) "
                           "INNER JOIN ansprechpartner USING(ansID) "
                           "INNER JOIN ansprechVerwaltung ON ansprechVerwaltung.aVerwaltungID = projekt.dozentID "
                           "WHERE projekt.proID = :proID;");

        query.prepare (statement);
        query.bindValue (":proID", id);
        query.exec ();




        QStringList list;
        list << "student.vorname" << "student.nachname" << "projekt.proName" << "projekt.proBesc" << "projekt.proHin";
        list << "projekt.proStatus" << "organisation.orgName" << "ansprechpartner.vorname" << "ansprechpartner.nachname";
        list << "ansprechVerwaltung.vorname" << "ansprechVerwaltung.nachname";

        QList<QMap<QString, QString>*>* projectList = new QList<QMap<QString, QString>*>();
        while (query.next ()) {
                QMap<QString, QString>* projectData = new QMap<QString, QString>();
                for (int i = 0; i < list.length (); i++) {
                        projectData->insert (list.at (i), query.value (list.at (i)).toString ());
                }
                projectList->append (projectData);
        }
        return projectList;
}



