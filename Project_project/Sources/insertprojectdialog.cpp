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
        db->printAll ();
        delete ui;
}


void InsertProjectDialog::loadOrg ()
{
        ui->orgCombo->clear ();
        for (int i = 0; i < db->getOrganisationen ()->length (); i++) {
                ui->orgCombo->insertItem (i, db->getOrganisationen ()->at (i)->getOrganisationName ());
        }
        ui->orgCombo->setCurrentIndex (0);
}

void InsertProjectDialog::loadAns (int id)
{
        ui->ansCombo->clear ();
        for (int i = 0; i < db->getAnsprechpartner ()->length (); i++) {
                if (db->getAnsprechpartner ()->at (i)->getForeignKey () == id + 1) {
                        ui->ansCombo->addItem (db->getAnsprechpartner ()->at (i)->getVorname () + " " + db->getAnsprechpartner ()->at (i)->getNachname ());
                }
        }
        ui->ansCombo->setCurrentIndex (0);
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
        ui->stuCombo1->setCurrentIndex (0);
        ui->stuCombo2->setCurrentIndex (0);
        ui->stuCombo3->setCurrentIndex (0);
}

void InsertProjectDialog::loadDozenten ()
{
        ui->dozentCombo->clear ();
        for (int i = 0; i < db->getAnsprechVerwaltung ()->length (); i++) {
                ui->dozentCombo->insertItem (i, db->getAnsprechVerwaltung ()->at (i)->getVorname () + " " + db->getAnsprechVerwaltung ()->at (i)->getNachname ());
        }
        ui->dozentCombo->setCurrentIndex (0);
}

void InsertProjectDialog::pushStudenten (bool abletopush)
{
        if (abletopush) {
                Gruppe* newGruppe = new Gruppe (0, 0);
                db->getGruppen ()->append (newGruppe);
                db->saveGruppen ();
                db->loadGruppen ();
                auto name1 = ui->stuCombo1->currentText ().split (" ");
                auto name2 = ui->stuCombo2->currentText ().split (" ");
                Student* newStudent1 = new Student (0, name1.at (0), name1.at (1), db->getGruppen ()->last ()->getPrimaryKey ());
                Student* newStudent2 = new Student (0, name2.at (0), name2.at (1), db->getGruppen ()->last ()->getPrimaryKey ());
                db->getStudenten ()->append (newStudent1);
                db->saveStudenten ();
                db->loadStudenten ();
                db->getStudenten ()->append (newStudent2);
                db->saveStudenten ();
                db->loadStudenten ();
                if (ui->stuCombo3->currentIndex () > 0) {
                        auto name3 = ui->stuCombo3->currentText ().split (" ");
                        Student* newStudent3 = new Student (0, name3.at (0), name3.at (1), db->getGruppen ()->last ()->getPrimaryKey ());
                        db->getStudenten ()->append (newStudent3);
                        db->saveStudenten ();
                        db->loadStudenten ();
                }
        }
}

void InsertProjectDialog::pushProject (bool abletopush)
{
        if (abletopush) {
                Projekt* newProject = new Projekt (0, ui->orgCombo->currentIndex () + 1, db->getGruppen ()->last ()->getPrimaryKey (), ui->dozentCombo->currentIndex () + 1, ui->projectnameInput->text (), ui->bescInput->toPlainText (), ui->hintInput->toPlainText (), 0);
                db->getProjekte ()->append (newProject);
                db->saveProjekte ();
                db->loadProjekte ();
                db->getGruppen ()->last ()->setForeignKey (db->getProjekte ()->last ()->getPrimaryKey ());
                db->saveGruppen ();
                db->loadGruppen ();
        }
}

void InsertProjectDialog::on_orgCombo_currentIndexChanged (int index)
{
        loadAns (index);
}

void InsertProjectDialog::on_bescInput_selectionChanged ()
{
}

void InsertProjectDialog::on_hintInput_selectionChanged ()
{
}

void InsertProjectDialog::on_buttonBox_accepted ()
{
        bool ableToPush = false;

        if (ui->orgCombo->currentIndex () >= 0) {
                if (ui->ansCombo->currentIndex () >= 0) {
                        if (ui->stuCombo1->currentIndex () > 0) {
                                if (ui->stuCombo2->currentIndex () > 0) {
                                        if (ui->dozentCombo->currentIndex () >= 0) {
                                                if (!(ui->projectnameInput->text ().isNull () || ui->projectnameInput->text ().isEmpty ())) {
                                                        if (ui->bescInput->toPlainText () != "") {
                                                                if (ui->hintInput->toPlainText () != "") {
                                                                        ableToPush = true;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
        pushStudenten (ableToPush);
        pushProject (ableToPush);
        this->accept ();
}

void InsertProjectDialog::on_buttonBox_rejected ()
{
        this->reject ();
}
