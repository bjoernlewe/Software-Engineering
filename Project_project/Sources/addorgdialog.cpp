#include "Headers/addorgdialog.h"
#include "ui_addorgdialog.h"

AddOrgDialog::AddOrgDialog(QWidget *parent) :
        QDialog (parent),
        ui (new Ui::addOrgDialog)
{
        ui->setupUi (this);
}

AddOrgDialog::~AddOrgDialog()
{
        delete ui;
}
