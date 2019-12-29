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
explicit InsertProjectDialog(QWidget *parent = nullptr);
~InsertProjectDialog();

private slots:
void on_ProIDLineEdit_editingFinished ();

void on_ProNameLineEdit_editingFinished ();

void on_BeschreibungLineEdit_editingFinished ();

void on_HintergrundLineEdit_editingFinished ();

void on_AnsprechLineEdit_editingFinished ();

void on_StudentLineEdit_editingFinished ();

void on_buttonBox_accepted ();

signals:
void insertNew (int projID, const QString& projName, const QString& projBesc, const QString& projHinter, const QString& projAnspr, const QString& projStudent);

private:
Ui::InsertProjectDialog *ui;
bool sendRequestFlag = false;
};

#endif // INSERTPROJECTDIALOG_H
