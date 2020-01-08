#include "Headers/addansdialog.h"
#include "ui_addansdialog.h"

AddAnsDialog::AddAnsDialog(QWidget *parent, DatabaseInterface* db, QStringList* orgList) :
        QDialog (parent),
        ui (new Ui::AddAnsDialog)
{
        ui->setupUi (this);
        if (db == nullptr) {
                this->db = new DatabaseInterface ();
        }
        else{
                this->db = db;
        }
        flag = false;
        ui->comboBox->addItems (*orgList);
}

AddAnsDialog::~AddAnsDialog()
{
        delete ui;
}

void AddAnsDialog::on_lineEdit_editingFinished ()
{
        flag = true;
}

void AddAnsDialog::on_lineEdit_2_editingFinished ()
{
        flag = true;
}

void AddAnsDialog::on_comboBox_currentIndexChanged (int index)
{
        if (!(index < 0 || index > ui->comboBox->count ()))
                flag = true;
}

void AddAnsDialog::on_buttonBox_accepted ()
{
        if (flag) {
                if (!(ui->lineEdit->text ().isNull () || ui->lineEdit->text ().isEmpty () || ui->lineEdit_2->text ().isNull () || ui->lineEdit_2->text ().isEmpty ())) {
                        Ansprechpartner* newAns = new Ansprechpartner (0, ui->lineEdit->text (), ui->lineEdit_2->text (), db->getOrganisationen ()->at (ui->comboBox->currentIndex ())->getPrimaryKey ());
                        db->getAnsprechpartner ()->append (newAns);
                        db->saveAnsprechpartner ();
                }
        }
}
