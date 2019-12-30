#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlError>
#include <QSqlRelation>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlField>

class DatabaseInterface : public QObject
{
Q_OBJECT
public:
explicit DatabaseInterface(QObject *parent = nullptr);

void newEntry (int projID, const QString& projName, const QString& projBesc, const QString& projHinter, const QString& projAnspr, const QString& projStudent1, const QString& projStudent2, const QString& projStudent3);

QStringList* getNames (QString tablename);

QStringList* getOrg ();

void refresh ();

QStandardItemModel *getModel () const;
void setModel (QStandardItemModel *value);

QTableView *getProfView () const;
void setProfView (QTableView *value);

QTableView *getStuView () const;
void setStuView (QTableView *value);

private slots:
void refreshData ();

private:
QSqlDatabase db;
QStandardItemModel* model;
QTableView* profView;
QTableView* stuView;
bool createConnection ();
void initializeModel (QStandardItemModel *model);
void getValuesFromDatabase (QStandardItemModel* model);
QTableView *createView (QStandardItemModel *model, const QString &title = "");
void createRT ();

signals:

public slots:
};

#endif // DATABASEINTERFACE_H
