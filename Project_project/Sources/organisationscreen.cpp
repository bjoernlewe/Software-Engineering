#include "Headers/organisationscreen.h"
#include "ui_organisationscreen.h"

OrganisationScreen::OrganisationScreen(QWidget *parent, DatabaseInterface* db) :
        QDialog (parent),
        ui (new Ui::OrganisationScreen)
{
        ui->setupUi (this);
        if (db == nullptr) {
                db = new DatabaseInterface ();
        }
        else{
                this->db = db;
        }
        loadTableItems (0);
        loadOrgList ();
}

OrganisationScreen::~OrganisationScreen()
{
        delete ui;
}

void OrganisationScreen::on_addOrg_clicked ()
{
        AddOrgDialog a (this);

        a.exec ();
}

void OrganisationScreen::on_remOrg_clicked ()
{
}

void OrganisationScreen::on_addAns_clicked ()
{
        QStringList list;

        for (int i = 0; i < db->getOrganisationen ()->length (); i++) {
                list.append (db->getOrganisationen ()->at (i)->getOrganisationName ());
        }
        AddAnsDialog a (this, db, &list);

        a.exec ();
}

void OrganisationScreen::on_remAns_clicked ()
{
        db->getAnsprechpartner ()->removeAt (lastRow);
        loadTableItems (lastRow - 1);
}

void OrganisationScreen::on_OrgList_currentRowChanged (int currentRow)
{
        loadTableItems (currentRow);
}

void OrganisationScreen::loadOrgList ()
{
        QStringList list;

        ui->OrgList->clear ();

        for (int i = 0; i < db->getOrganisationen ()->length (); i++) {
                list.append (db->getOrganisationen ()->at (i)->getOrganisationName ());
        }

        ui->OrgList->addItems (list);
}

void OrganisationScreen::loadTableItems (int id)
{
        QStringList list;

        ui->AnsprechpartnerTable->clear ();

        for (int i = ui->AnsprechpartnerTable->rowCount () - 1; i >= 0; i--) {
                ui->AnsprechpartnerTable->removeRow (i);
        }
        list.append ("Vorname");
        list.append ("Nachname");
        ui->AnsprechpartnerTable->setHorizontalHeaderLabels (list);

        for (int i = 0; i < db->getAnsprechpartner ()->length (); i++) {
                if (db->getAnsprechpartner ()->at (i)->getForeignKey () == id + 1) {
                        QTableWidgetItem* vorname = new QTableWidgetItem (db->getAnsprechpartner ()->at (i)->getVorname ());
                        QTableWidgetItem* nachname = new QTableWidgetItem (db->getAnsprechpartner ()->at (i)->getNachname ());
                        ui->AnsprechpartnerTable->insertRow (ui->AnsprechpartnerTable->rowCount ());
                        ui->AnsprechpartnerTable->setItem (ui->AnsprechpartnerTable->rowCount () - 1, 0, vorname);
                        ui->AnsprechpartnerTable->setItem (ui->AnsprechpartnerTable->rowCount () - 1, 1, nachname);
                }
        }
}

void OrganisationScreen::on_AnsprechpartnerTable_cellChanged (int row, int column)
{
        lastRow = row;
        Q_UNUSED (column)
}

void OrganisationScreen::on_buttonBox_accepted ()
{
        db->saveOrganisation ();
        db->saveAnsprechpartner ();
        this->accept ();
}

void OrganisationScreen::on_buttonBox_rejected ()
{
        this->reject ();
}
