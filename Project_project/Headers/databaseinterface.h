#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlError>
#include <QSqlRelation>
#include <QAbstractItemView>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlRecord>
#include <QSqlField>
#include <QVector>
#include <QStringListModel>
#include <QTreeView>
#include <QListView>
#include <QDataWidgetMapper>
#include <QComboBox>

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

void removeOrgAt (int id);
void removeAnsAt (int id);

int getMaxID (QVector<Ansprechpartner*>* tmp);
int getMaxID (QVector<Student*>* tmp);
int getMaxID (QVector<Gruppe*>* tmp);
int getMaxID (QVector<Projekt*>* tmp);
int getMaxID (QVector<Organisation*>* tmp);
int getMaxID (QVector<DozentVerwaltung*>* tmp);
int getMaxID (QVector<StudentVerwaltung*>* tmp);
int getMaxID (QVector<Verwaltung*>* tmp);

void getStudentComboItems (QComboBox* box);
void getOrgComboItems (QComboBox* box);
void getAnsprechComboItems (QComboBox* box);
void getDozentComboItems (QComboBox* box);
void getView (QListView* view, const QString& type, int id);
void getItemView (QTreeView* view, const QString& type, int id);
void getMappedWidget (QDataWidgetMapper* mapper, QList<QWidget*> widgets, const QString& type, int id);

void changeIndex (const QModelIndex &index);

QList<QMap<QString, QString>*>* getOneProject (int id);

void printAll ();

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

QStandardItemModel *getModel () const;
void setModel (QStandardItemModel *value);

QModelIndex *getIndex () const;
void setIndex (QModelIndex *value);

QStringListModel *getListmodel () const;
void setListmodel (QStringListModel *value);

QMap<int, QString> getKEYS () const;
void setKEYS (const QMap<int, QString> &value);

private:
QSqlDatabase db;
QStandardItemModel* model;
QStringListModel* listmodel;
QModelIndex* index;
QMap<int, QString> KEYS;

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
void initializeDatabase ();
QList<int> getProjektID (const QString& type, int id);
void getValuesFromDatabase (QStandardItemModel* model, const QString& type, int id);
void getValuesFromDatabase (QStringListModel* model, const QString& type, int id);
};

#endif // DATABASEINTERFACE_H
