#ifndef ADDORGDIALOG_H
#define ADDORGDIALOG_H

#include <QDialog>

namespace Ui {
class addOrgDialog;
}

class AddOrgDialog : public QDialog
{
Q_OBJECT

public:
explicit AddOrgDialog(QWidget *parent = nullptr);
~AddOrgDialog();

private:
Ui::addOrgDialog *ui;
};

#endif // ADDORGDIALOG_H
