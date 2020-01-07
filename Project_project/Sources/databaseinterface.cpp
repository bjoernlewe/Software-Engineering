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


        model = new QStandardItemModel ();
        initializeModel (model);
        profView = createView (model, "Dozentenansicht");
        profView->setFont (QFont ("Times", 20, QFont::Bold));
        stuView = createView (model, "Studentenansicht");
}

void DatabaseInterface::loadTables ()
{
        studenten->clear ();
        gruppen->clear ();
        projekte->clear ();
        organisationen->clear ();
        ansprechpartner->clear ();

        QSqlQuery query;

        query.exec ("SELECT * FROM student;");

        while (query.next ()) {
                Student* newStudent = new Student (query.value ("studentID").toInt (), query.value ("vorname").toString (), query.value ("nachname").toString (), query.value ("gruID").toInt ());
                studenten->append (newStudent);
        }

        if (query.lastError ().isValid ()) {
                qDebug () << query.lastError ();
                return;
        }

        query.clear ();

        query.exec ("SELECT * FROM gruppe");

        while (query.next ()) {
                Gruppe* newGroup = new Gruppe (query.value ("gruID").toInt (), query.value ("proID").toInt ());
                gruppen->append (newGroup);
        }

        if (query.lastError ().isValid ()) {
                qDebug () << query.lastError ();
                return;
        }

        query.clear ();

        query.exec ("SELECT * FROM projekt");

        while (query.next ()) {
                bool status = query.value ("proStatus") == 0 ? static_cast<bool>(nullptr) : query.value ("proStatus").toBool ();
                Projekt* newProject = new Projekt (query.value ("proID").toInt (), query.value ("orgID").toInt (), query.value ("gruID").toInt (), query.value ("proName").toString (), query.value ("proBesc").toString (), query.value ("proHin").toString (), status);
                projekte->append (newProject);
        }

        if (query.lastError ().isValid ()) {
                qDebug () << query.lastError ();
                return;
        }

        query.clear ();

        query.exec ("SELECT * FROM organisation");

        while (query.next ()) {
                Organisation* newOrg = new Organisation (query.value ("orgID").toInt (), query.value ("proID").toInt (), query.value ("ansID").toInt (), query.value ("orgName").toString ());
                organisationen->append (newOrg);
        }

        if (query.lastError ().isValid ()) {
                qDebug () << query.lastError ();
                return;
        }

        query.clear ();

        query.exec ("SELECT * FROM ansprechpartner");

        while (query.next ()) {
                Ansprechpartner* newAnsprech = new Ansprechpartner (query.value ("ansID").toInt (), query.value ("vorname").toString (), query.value ("nachname").toString (), query.value ("orgID").toInt ());
                ansprechpartner->append (newAnsprech);
        }

        if (query.lastError ().isValid ()) {
                qDebug () << query.lastError ();
                return;
        }
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
}

void DatabaseInterface::refresh ()
{
        refreshData ();
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

bool DatabaseInterface::createConnection ()
{
        if (!db.isOpen ())
                db = QSqlDatabase::addDatabase ("QSQLITE");

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
                qDebug () << db.lastError ();
                return false;
        }
        qDebug () << db.commit ();
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
}

QTableView *DatabaseInterface::createView (QStandardItemModel *model, const QString &title)
{
        QTableView *view = new QTableView;

        view->setModel (model);
        view->setWindowTitle (title);
        return view;
}
