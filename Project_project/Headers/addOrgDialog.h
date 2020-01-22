#ifndef ADDORGDIALOG_H
#define ADDORGDIALOG_H

#include <QDialog>
#include "databaseinterface.h"

namespace Ui {
class AddOrgDialog;
}

class AddOrgDialog : public QDialog
{
Q_OBJECT

public:
explicit AddOrgDialog(QWidget *parent = nullptr, DatabaseInterface* db = nullptr);
~AddOrgDialog();

private slots:
void on_buttonBox_accepted ();

void on_buttonBox_rejected ();

private:
Ui::AddOrgDialog *ui;
DatabaseInterface* db;
};

#endif // ADDORGDIALOG_H
