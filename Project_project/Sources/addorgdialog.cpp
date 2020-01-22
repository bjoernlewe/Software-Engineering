#include "Headers/addorgdialog.h"
#include "ui_addorgdialog.h"

AddOrgDialog::AddOrgDialog(QWidget *parent, DatabaseInterface* db) :
        QDialog (parent),
        ui (new Ui::AddOrgDialog)
{
        ui->setupUi (this);
        if (db == nullptr) {
                this->db = new DatabaseInterface ();
        }
        else{
                this->db = db;
        }
}

AddOrgDialog::~AddOrgDialog()
{
        delete ui;
}

void AddOrgDialog::on_buttonBox_accepted ()
{
        if (!(ui->lineEdit->text ().isNull () || ui->lineEdit->text ().isEmpty ())) {
                Organisation* newOrg = new Organisation (0, 0, 0, ui->lineEdit->text ());
                db->getOrganisationen ()->append (newOrg);
                db->saveOrganisation ();
                db->loadOrganisation ();
                this->accept ();
        }
        else{
                this->reject ();
        }
}

void AddOrgDialog::on_buttonBox_rejected ()
{
        this->reject ();
}
