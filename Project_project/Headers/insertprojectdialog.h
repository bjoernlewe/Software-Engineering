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
explicit InsertProjectDialog(QWidget *parent = nullptr, DatabaseInterface* db = nullptr);
~InsertProjectDialog();

private slots:

void on_orgCombo_currentIndexChanged (int index);

void on_bescInput_selectionChanged ();

void on_hintInput_selectionChanged ();

void on_buttonBox_accepted ();

void on_buttonBox_rejected ();

private:
DatabaseInterface* db;
Ui::InsertProjectDialog *ui;
void loadOrg ();
void loadAns (int id);
void loadStudenten ();
void loadDozenten ();
void pushStudenten (bool abletopush);
void pushProject (bool abletopush);
};

#endif // INSERTPROJECTDIALOG_H
