#include "Headers/insertprojectdialog.h"
#include "ui_insertprojectdialog.h"

InsertProjectDialog::InsertProjectDialog(QWidget *parent, DatabaseInterface* db) :
        QDialog (parent),
        ui (new Ui::InsertProjectDialog)
{
        if (db == nullptr) {
                this->db = new DatabaseInterface ();
        }
        else{
                this->db = db;
        }
        ui->setupUi (this);
        loadStudenten ();
        loadDozenten ();
        loadOrg ();
        loadAns (0);
}

InsertProjectDialog::~InsertProjectDialog()
{
        qDebug () << "InsertProjectDialog::~InsertProjectDialog()";
        delete ui;
}


void InsertProjectDialog::loadOrg ()
{
        ui->orgCombo->clear ();
        for (int i = 0; i < db->getOrganisationen ()->length (); i++) {
                ui->orgCombo->insertItem (i, db->getOrganisationen ()->at (i)->getOrganisationName ());
        }
}

void InsertProjectDialog::loadAns (int id)
{
        ui->ansCombo->clear ();
        for (int i = 0; i < db->getAnsprechpartner ()->length (); i++) {
                if (db->getAnsprechpartner ()->at (i)->getForeignKey () == id + 1) {
                        ui->ansCombo->addItem (db->getAnsprechpartner ()->at (i)->getVorname () + " " + db->getAnsprechpartner ()->at (i)->getNachname ());
                }
        }
}

void InsertProjectDialog::loadStudenten ()
{
        ui->stuCombo1->clear ();
        ui->stuCombo2->clear ();
        ui->stuCombo3->clear ();
        ui->stuCombo1->insertItem (0, "");
        ui->stuCombo2->insertItem (0, "");
        ui->stuCombo3->insertItem (0, "");
        for (int i = 0; i < db->getStudentenverwaltung ()->length (); i++) {
                ui->stuCombo1->insertItem (i + 1, db->getStudentenverwaltung ()->at (i)->getVorname () + " " + db->getStudentenverwaltung ()->at (i)->getNachname ());
                ui->stuCombo2->insertItem (i + 1, db->getStudentenverwaltung ()->at (i)->getVorname () + " " + db->getStudentenverwaltung ()->at (i)->getNachname ());
                ui->stuCombo3->insertItem (i + 1, db->getStudentenverwaltung ()->at (i)->getVorname () + " " + db->getStudentenverwaltung ()->at (i)->getNachname ());
        }
}

void InsertProjectDialog::loadDozenten ()
{
        ui->dozentCombo->clear ();
        for (int i = 0; i < db->getAnsprechVerwaltung ()->length (); i++) {
                ui->dozentCombo->insertItem (i, db->getAnsprechVerwaltung ()->at (i)->getVorname () + " " + db->getAnsprechVerwaltung ()->at (i)->getNachname ());
        }
}

void InsertProjectDialog::on_orgCombo_currentIndexChanged (int index)
{
        loadAns (index);
}

void InsertProjectDialog::on_bescInput_selectionChanged ()
{
        qDebug () << "beschreibung activated";
}

void InsertProjectDialog::on_hintInput_selectionChanged ()
{
        qDebug () << "hintergrund activated";
}
