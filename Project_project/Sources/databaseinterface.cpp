#include "Headers/databaseinterface.h"

DatabaseInterface::DatabaseInterface(QObject *parent) : QObject (parent)
{
        if (!createConnection ()) {
                throw QString ("Could not create a Connection");
        }
        model = new QStandardItemModel ();
        initializeModel (model);
        profView = createView (model, "Dozentenansicht");
        profView->setFont (QFont ("Times", 20, QFont::Bold));
        stuView = createView (model, "Studentenansicht");
}

void DatabaseInterface::newEntry (int projID, const QString &projName, const QString &projBesc, const QString &projHinter, const QString &projAnspr, const QString &projStudent)
{
        qDebug () << "DatabaseInterface::newEntry ()";
        QSqlQuery query;

        query.prepare ("INSERT INTO project "
                "(proID,orgID,gruID,proName,proBesc,proHin) "
                "VALUES (:projID, NULL, NULL,:projName,:projBesc, :projHinter)");
        query.bindValue (":projID", projID);
        query.bindValue (":projName", projName);
        query.bindValue (":projBesc", projBesc);
        query.bindValue (":projHinter", projHinter);
        query.exec ();
        db.commit ();
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
        QStringList labelList;

        labelList.append (QString ("ProjektID"));
        labelList.append (QString ("Projektname"));
        labelList.append (QString ("Projektbeschreibung"));
        labelList.append (QString ("Projekthintergrund"));
        labelList.append (QString ("Ansprechpartner"));
        labelList.append (QString ("Studenten"));

        model->setHorizontalHeaderLabels (labelList);

        getValuesFromDatabase (model);


        //Prints SQL Tables
//        for (int i = 0; i < db.tables ().length (); i++) {
//                auto returnValue = db.record (db.tables ().at (i));
//                qDebug () << returnValue;
//        }
}

void DatabaseInterface::getValuesFromDatabase (QStandardItemModel* model)
{
        QString execString ("SELECT student.vorname, student.nachname,"
                            "projekt.proID,projekt.proName, projekt.proBesc,projekt.proHin,"
                            "organisation.orgName,"
                            "ansprechpartner.vorname,ansprechpartner.nachname "
                            "FROM student NATURAL JOIN gruppe "
                            "NATURAL JOIN projekt "
                            "NATURAL JOIN organisation "
                            "INNER JOIN ansprechpartner "
                            "ON organisation.orgID = ansprechpartner.orgID;");

        QSqlQuery query (execString);

        if (query.lastError ().isValid ()) {
                qDebug () << query.lastError ();
        }

        while (query.next ()) {
                QList<QStandardItem*> items;
                QString stuName = query.value ("student.vorname").toString ();
                stuName += " " + query.value ("student.nachname").toString ();
                QString proID = query.value ("proID").toString ();
                QString proName = query.value ("proName").toString ();
                QString besc = query.value ("proBesc").toString ();
                QString hint = query.value ("proHin").toString ();
                QString orgName = query.value ("orgName").toString ();
                QString ansName = query.value ("ansprechpartner.vorname").toString ();
                ansName += " " + query.value ("ansprechpartner.nachname").toString ();

                QStandardItem* proNameItem = new QStandardItem (proName);

                QStandardItem* proBescItem = new QStandardItem (besc);

                QStandardItem* proHinterItem = new QStandardItem (hint);

                QStandardItem* proAnsItem = new QStandardItem (ansName);

                QStandardItem* proStuItem = new QStandardItem (stuName);

                QStandardItem* id = new QStandardItem (proID);

                items.append (id);
                items.append (proNameItem);
                items.append (proBescItem);
                items.append (proHinterItem);
                items.append (proAnsItem);
                items.append (proStuItem);
                model->insertRow (model->rowCount (), items);
        }
}

QTableView *DatabaseInterface::createView (QStandardItemModel *model, const QString &title)
{
        QTableView *view = new QTableView;

        view->setModel (model);
        view->setWindowTitle (title);
        return view;
}
