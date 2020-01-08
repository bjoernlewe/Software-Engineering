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
        ansprechVerwaltung = new QVector<AnsprechVerwaltung*>();


        model = new QStandardItemModel ();
        initializeModel (model);
        profView = createView (model, "Dozentenansicht");
        profView->setFont (QFont ("Times", 20, QFont::Bold));
        stuView = createView (model, "Studentenansicht");
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
                qDebug () << "Student(" << studenten->at (i)->getPrimaryKey () << "|" << studenten->at (i)->getForeignKey () << "|" << studenten->at (i)->getVorname () << "|" << studenten->at (i)->getNachname () << ")";
        }

        for (int i = 0; i < gruppen->length (); i++) {
                qDebug () << "Gruppe(" << gruppen->at (i)->getPrimaryKey () << "|" << gruppen->at (i)->getForeignKey () << ")";
        }

        for (int i = 0; i < projekte->length (); i++) {
                qDebug () << "Projekt(" << projekte->at (i)->getPrimaryKey () << "|" << projekte->at (i)->getForeignOrgKey () << "|" << projekte->at (i)->getForeignGruKey () << "|" << projekte->at (i)->getProjektName () << "|" << projekte->at (i)->getBeschreibung () << "|" << projekte->at (i)->getHintergrund () << "|" << projekte->at (i)->getStatus () << "|" << ")";
        }

        for (int i = 0; i < organisationen->length (); i++) {
                qDebug () << "Organisation(" << organisationen->at (i)->getPrimaryKey () << "|" << organisationen->at (i)->getForeignAnsKey () << "|" << organisationen->at (i)->getForeignProKey () << "|" << organisationen->at (i)->getOrganisationName () << ")";
        }

        for (int i = 0; i < ansprechpartner->length (); i++) {
                qDebug () << "Ansprechpartner(" << ansprechpartner->at (i)->getPrimaryKey () << "|" << ansprechpartner->at (i)->getForeignKey () << "|" << ansprechpartner->at (i)->getVorname () << "|" << ansprechpartner->at (i)->getNachname () << ")";
        }

        for (int i = 0; i < verwaltung->length (); i++) {
                qDebug () << "(" << verwaltung->at (i)->getPrimaryKey () << "|" << verwaltung->at (i)->getForeignStuKey () << "|" << verwaltung->at (i)->getForeignAnsKey () << ")";
        }

        for (int i = 0; i < ansprechVerwaltung->length (); i++) {
                qDebug () << "(" << ansprechVerwaltung->at (i)->getPrimaryKey () << "|" << ansprechVerwaltung->at (i)->getForeignKey () << "|" << ansprechVerwaltung->at (i)->getUserName () << "|" << ansprechVerwaltung->at (i)->getPassword () << ")";
        }

        for (int i = 0; i < studentenverwaltung->length (); i++) {
                qDebug () << "(" << studentenverwaltung->at (i)->getPrimaryKey () << "|" << studentenverwaltung->at (i)->getForeignKey () << "|" << studentenverwaltung->at (i)->getUserName () << "|" << studentenverwaltung->at (i)->getPassword () << ")";
        }
}


QStandardItemModel *DatabaseInterface::getModel () const
{
        return model;
}

void DatabaseInterface::setModel (QStandardItemModel *value)
{
        model = value;
}

QTableView *DatabaseInterface::getProfView () const
{
        return profView;
}

void DatabaseInterface::setProfView (QTableView *value)
{
        profView = value;
}

QTableView *DatabaseInterface::getStuView () const
{
        return stuView;
}

void DatabaseInterface::setStuView (QTableView *value)
{
        stuView = value;
}

void DatabaseInterface::refreshData ()
{
        getValuesFromDatabase (this->model);
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
                Projekt* newProject = new Projekt (query.value ("proID").toInt (), query.value ("orgID").toInt (), query.value ("gruID").toInt (), query.value ("proName").toString (), query.value ("proBesc").toString (), query.value ("proHin").toString (), status);
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
                StudentVerwaltung* newSVerwaltung = new StudentVerwaltung (query.value ("sVerwaltungID").toInt (), query.value ("verwaltungID").toInt (), query.value ("userName").toString (), query.value ("passwort").toString ());
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
        ansprechVerwaltung->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM ansprechVerwaltung");

        while (query.next ()) {
                AnsprechVerwaltung* newAVerwaltung = new AnsprechVerwaltung (query.value ("aVerwaltungID").toInt (), query.value ("verwaltungID").toInt (), query.value ("userName").toString (), query.value ("passwort").toString ());
                ansprechVerwaltung->append (newAVerwaltung);
        }

        ansVerwaltungOriginalSize = ansprechVerwaltung->length ();

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
                query.bindValue ("gruID", gruppen->at (i)->getPrimaryKey () <= 0 ? getMaxID (gruppen) + 1 : gruppen->at (i)->getPrimaryKey ());
                query.bindValue ("proID", gruppen->at (i)->getForeignKey ());
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

        QString statement = "INSERT INTO projekt (proID,orgID,gruID,proName,proBesc,proHin,proStatus)"
                            "VALUES (:proID,:orgID,:gruID,:proName,:proBesc,:proHin,:proStatus)"
                            "ON CONFLICT(proID) DO UPDATE SET "
                            "orgID = excluded.orgID, "
                            "gruID = excluded.gruID, "
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
        QString statement = "INSERT INTO studentVerwaltung (sVerwaltungID,verwaltungID,userName,passwort)"
                            "VALUES (:sVerwaltungID,:verwaltungID,:userName,:passwort)"
                            "ON CONFLICT(sVerwaltungID) DO UPDATE SET "
                            "verwaltungID = excluded.verwaltungID, "
                            "userName = excluded.userName, "
                            "passwort = excluded.passwort "
                            "WHERE sVerwaltungID = excluded.sVerwaltungID;";

        for (int i = 0; i < studentenverwaltung->length (); i++) {
                query.prepare (statement);
                query.bindValue (":sVerwaltungID", studentenverwaltung->at (i)->getPrimaryKey () <= 0 ? getMaxID (studentenverwaltung) + 1 : studentenverwaltung->at (i)->getPrimaryKey ());
                query.bindValue (":verwaltungID", studentenverwaltung->at (i)->getForeignKey ());
                query.bindValue (":userName", studentenverwaltung->at (i)->getUserName ());
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
        QString statement = "INSERT INTO ansprechVerwaltung (aVerwaltungID,verwaltung,userName,passwort)"
                            "VALUES (:aVerwaltungID,:verwaltungID,:userName,:passwort)"
                            "ON CONFLICT(aVerwaltungID) DO UPDATE SET "
                            "verwaltungID = excluded.verwaltungID, "
                            "userName = excluded.userName, "
                            "passwort = excluded.passwort "
                            " WHERE aVerwaltungID = excluded.aVerwaltungID;";

        for (int i = 0; i < ansprechVerwaltung->length (); i++) {
                query.prepare (statement);
                query.bindValue (":aVerwaltungID", ansprechVerwaltung->at (i)->getPrimaryKey () <= 0 ? getMaxID (ansprechVerwaltung) + 1 : ansprechVerwaltung->at (i)->getPrimaryKey ());
                query.bindValue (":verwaltungID", ansprechVerwaltung->at (i)->getForeignKey ());
                query.bindValue (":userName", ansprechVerwaltung->at (i)->getUserName ());
                query.bindValue (":passwort", ansprechVerwaltung->at (i)->getPassword ());
                query.exec ();
                if (query.lastError ().isValid ()) {
                        qDebug () << "saveAnsprechverwaltung: " << i << query.lastError ();
                        return;
                }
                query.clear ();
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
        return buffer->getPrimaryKey ();
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
        return buffer->getPrimaryKey ();
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
        return buffer->getPrimaryKey ();
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
        return buffer->getPrimaryKey ();
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
        return buffer->getPrimaryKey ();
}

int DatabaseInterface::getMaxID (QVector<AnsprechVerwaltung *> *tmp)
{
        AnsprechVerwaltung* buffer = nullptr;

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
        return buffer->getPrimaryKey ();
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
        return buffer->getPrimaryKey ();
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
        return buffer->getPrimaryKey ();
}

QVector<AnsprechVerwaltung *> *DatabaseInterface::getAnsprechVerwaltung () const
{
        return ansprechVerwaltung;
}

void DatabaseInterface::setAnsprechVerwaltung (QVector<AnsprechVerwaltung *> *value)
{
        ansprechVerwaltung = value;
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
        if (!db.isOpen ()) {
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

void DatabaseInterface::initializeModel (QStandardItemModel *model)
{
        getValuesFromDatabase (model);

        loadTables ();

        printAll ();
}

void DatabaseInterface::getValuesFromDatabase (QStandardItemModel* model)
{
        Q_UNUSED (model)
}

QTableView *DatabaseInterface::createView (QStandardItemModel *model, const QString &title)
{
        QTableView *view = new QTableView;

        view->setModel (model);
        view->setWindowTitle (title);
        return view;
}

