#ifndef INSERTPROJECTDIALOG_H
#define INSERTPROJECTDIALOG_H

#include <QDialog>
#include "databaseinterface.h"

namespace Ui {
class InsertProjectDialog;
}

class InsertProjectDialog : public QDialog
{
Q_OBJECT

public:
explicit InsertProjectDialog(QWidget *parent = nullptr, QStringList* ansprechpartner = nullptr, QStringList* studenten = nullptr, QStringList* org = nullptr);
~InsertProjectDialog();

private slots:

void on_ProNameLineEdit_editingFinished ();

void on_BeschreibungLineEdit_editingFinished ();

void on_HintergrundLineEdit_editingFinished ();

void on_buttonBox_accepted ();

void on_AnsprechpartnerCombo_currentIndexChanged (int index);

void on_StudentCombo1_currentIndexChanged (int index);

void on_StudentCombo2_currentIndexChanged (int index);

void on_StudentCombo3_currentIndexChanged (int index);

void on_OrganisationCombo_currentIndexChanged (int index);

signals:
void insertNew (const QString& projName, const QString& projBesc, const QString& projHinter, const QString& projAnspr, const QString& projStudent1, const QString& projStudent2, const QString& projStudent3);

private:
Ui::InsertProjectDialog *ui;
bool sendRequestFlag = false;
QStringList* ansprechpartner;
QStringList* studenten;
QStringList* organisation;
};

#endif // INSERTPROJECTDIALOG_H
