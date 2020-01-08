#ifndef ADDANSDIALOG_H
#define ADDANSDIALOG_H

#include <QDialog>
#include "Headers/databaseinterface.h"

namespace Ui {
class AddAnsDialog;
}

class AddAnsDialog : public QDialog
{
Q_OBJECT

public:
explicit AddAnsDialog(QWidget *parent = nullptr, DatabaseInterface* db = nullptr, QStringList* orgList = nullptr);
~AddAnsDialog();

private slots:
void on_lineEdit_editingFinished ();

void on_lineEdit_2_editingFinished ();

void on_comboBox_currentIndexChanged (int index);

void on_buttonBox_accepted ();

private:
Ui::AddAnsDialog *ui;
DatabaseInterface* db;
bool flag;
};

#endif // ADDANSDIALOG_H
