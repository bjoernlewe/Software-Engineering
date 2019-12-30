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

void DatabaseInterface::newEntry (int projID, const QString &projName, const QString &projBesc, const QString &projHinter, const QString &projAnspr, const QString& projStudent1, const QString& projStudent2, const QString& projStudent3)
{
        qDebug () << "DatabaseInterface::newEntry ()";
        QSqlQuery query1;

        query1.prepare ("INSERT INTO projekt "
                "(proID,orgID,gruID,proName,proBesc,proHin,proStatus) "
                "VALUES (:projID, NULL, NULL,:projName,:projBesc, :projHinter,0)");
        query1.bindValue (":projID", projID);
        query1.bindValue (":projName", projName);
        query1.bindValue (":projBesc", projBesc);
        query1.bindValue (":projHinter", projHinter);
        query1.exec ();

        qDebug () << "Anspechpartner: " << projAnspr;
        qDebug () << "Student 1: " << projStudent1;
        qDebug () << "Student 2: " << projStudent2;
        qDebug () << "Student 3: " << projStudent3;

//        QSqlQuery query2;
//        query2.prepare ("");
//        query2.bindValue (":ansID", "");
//        query2.bindValue (":ansprech", projAnspr);

        db.rollback ();
}

QStringList *DatabaseInterface::getNames (QString tablename)
{
        qDebug () << "DatabaseInterface::getNames(" << tablename << ")";
        if (tablename.isNull () || tablename.isEmpty ()) {
                throw QString ("DatabaseInterface::getNames : No tablename given");
        }

        QSqlQuery query;

        if (tablename == "student") {
                query.exec ("SELECT * FROM student ORDER BY 1 ASC");
        }
        else if (tablename == "ansprechpartner") {
                query.exec ("SELECT * FROM ansprechpartner ORDER BY 1 ASC");
        }
        else {
                throw QString ("DatabaseInterface::getNames : invalid table given");
        }

        QStringList* items = new QStringList ();
        while (query.next ()) {
                QString id;
                QString foreign;
                if (tablename == "student") {
                        id = query.value ("studentID").toString ();
                        foreign = query.value ("gruID").toString ();
                }
                else{
                        id = query.value ("ansID").toString ();
                        foreign = query.value ("orgID").toString ();
                }
                QString vorname = query.value ("vorname").toString ();
                QString nachname = query.value ("nachname").toString ();
                qDebug () << vorname << " " << nachname;
                items->append (id + " " + foreign + " " + vorname + " " + nachname);
        }
        return items;
}

QStringList *DatabaseInterface::getOrg ()
{
        QSqlQuery query;

        query.exec ("SELECT * FROM organisation ORDER BY 1 ASC");

        QStringList* items = new QStringList ();

        while (query.next ()) {
                QString orgid = query.value ("orgID").toString ();
                QString proforeign = query.value ("proID").toString ();
                QString ansforeign = query.value ("ansID").toString ();
                QString orgName = query.value ("orgName").toString ();
                items->append (orgid + " " + proforeign + " " + ansforeign + " " + orgName);
        }
        return items;
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
