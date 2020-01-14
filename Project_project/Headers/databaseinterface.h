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
#include <QVector>

#include "Headers/student.h"
#include "Headers/ansprechpartner.h"
#include "Headers/gruppe.h"
#include "Headers/organisation.h"
#include "Headers/projekt.h"
#include "Headers/dozentverwaltung.h"
#include "Headers/studentverwaltung.h"
#include "Headers/verwaltung.h"

class DatabaseInterface : public QObject
{
Q_OBJECT
public:
explicit DatabaseInterface(QObject *parent = nullptr);


void signIn (const QString& vorname, const QString& nachname, const QString& password, const QString& typ);

void loadTables ();

void saveTables ();

void loadGruppen ();
void loadStudenten ();
void loadProjekte ();
void loadAnsprechpartner ();
void loadOrganisation ();
void loadVerwaltung ();
void loadStudentenVerwaltung ();
void loadAnsprechVerwaltung ();


void saveGruppen ();
void saveStudenten ();
void saveProjekte ();
void saveAnsprechpartner ();
void saveOrganisation ();
void saveVerwaltung ();
void saveStudentenVerwaltung ();
void saveAnsprechVerwaltung ();

int getMaxID (QVector<Ansprechpartner*>* tmp);
int getMaxID (QVector<Student*>* tmp);
int getMaxID (QVector<Gruppe*>* tmp);
int getMaxID (QVector<Projekt*>* tmp);
int getMaxID (QVector<Organisation*>* tmp);
int getMaxID (QVector<DozentVerwaltung*>* tmp);
int getMaxID (QVector<StudentVerwaltung*>* tmp);
int getMaxID (QVector<Verwaltung*>* tmp);

void printAll ();

QStandardItemModel *getModel () const;
void setModel (QStandardItemModel *value);

QTableView *getProfView () const;
void setProfView (QTableView *value);

QTableView *getStuView () const;
void setStuView (QTableView *value);

QVector<Gruppe *> *getGruppen () const;
void setGruppen (QVector<Gruppe *> *value);

QVector<Student *> *getStudenten () const;
void setStudenten (QVector<Student *> *value);

QVector<Projekt *> *getProjekte () const;
void setProjekte (QVector<Projekt *> *value);

QVector<Ansprechpartner *> *getAnsprechpartner () const;
void setAnsprechpartner (QVector<Ansprechpartner *> *value);

QVector<Organisation *> *getOrganisationen () const;
void setOrganisationen (QVector<Organisation *> *value);

QVector<Verwaltung *> *getVerwaltung () const;
void setVerwaltung (QVector<Verwaltung *> *value);

QVector<StudentVerwaltung *> *getStudentenverwaltung () const;
void setStudentenverwaltung (QVector<StudentVerwaltung *> *value);

QVector<DozentVerwaltung *> *getAnsprechVerwaltung () const;
void setAnsprechVerwaltung (QVector<DozentVerwaltung *> *value);

private slots:
void refreshData ();

private:
QSqlDatabase db;
QStandardItemModel* model;
QTableView* profView;
QTableView* stuView;

int gruppeOriginalSize;
int studentenOriginalSize;
int projekteOriginalSize;
int ansprechOriginalSize;
int orgOriginalSize;
int verwaltungOriginalSize;
int stuVerwaltungOriginalSize;
int ansVerwaltungOriginalSize;

QVector<Gruppe*>* gruppen;
QVector<Student*>* studenten;
QVector<Projekt*>* projekte;
QVector<Ansprechpartner*>* ansprechpartner;
QVector<Organisation*>* organisationen;
QVector<Verwaltung*>* verwaltung;
QVector<StudentVerwaltung*>* studentenverwaltung;
QVector<DozentVerwaltung*>* dozentenverwaltung;

bool createConnection ();
void initializeModel (QStandardItemModel *model);
void getValuesFromDatabase (QStandardItemModel* model);
QTableView *createView (QStandardItemModel *model, const QString &title = "");
void createRT ();
};

#endif // DATABASEINTERFACE_H
