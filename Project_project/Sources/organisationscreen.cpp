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
        AddOrgDialog a (this, this->db);


        if (a.exec () == QDialog::Accepted) {
                ui->OrgList->update ();
                if (window ())
                        window ()->update ();
                update ();
        }
}

void OrganisationScreen::on_remOrg_clicked ()
{
        int rowClicked = ui->OrgList->currentRow ();

        qDebug () << "remove_Clicked at " << rowClicked;

        for (int i = 0; i < db->getAnsprechpartner ()->length (); i++) {
                if (db->getAnsprechpartner ()->at (i)->getForeignKey () == rowClicked) {
                        db->removeAnsAt (db->getAnsprechpartner ()->at (i)->getPrimaryKey ());
                        db->getAnsprechpartner ()->removeAt (i);
                }
        }
        db->removeOrgAt (db->getOrganisationen ()->at (rowClicked)->getPrimaryKey ());
        db->getOrganisationen ()->removeAt (rowClicked);
        loadOrgList ();
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
        int rowClicked = ui->AnsprechpartnerTable->currentRow ();
        int idInDataBase = -1;
        int idInList = -1;

        for (int i = 0; i < db->getAnsprechpartner ()->length (); i++) {
                if (ui->AnsprechpartnerTable->item (rowClicked, 0)->text () == db->getAnsprechpartner ()->at (i)->getVorname () ||
                    ui->AnsprechpartnerTable->item (rowClicked, 1)->text () == db->getAnsprechpartner ()->at (i)->getNachname ()) {
                        idInDataBase = db->getAnsprechpartner ()->at (i)->getPrimaryKey ();
                        idInList = i;
                }
        }

        qDebug () << "remove_Clicked at " << idInDataBase << ", " << idInList;

        db->getAnsprechpartner ()->removeAt (idInList);
        db->removeAnsAt (idInDataBase);
        loadTableItems (0);
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
