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

private:
Ui::InsertProjectDialog *ui;
};

#endif // INSERTPROJECTDIALOG_H
