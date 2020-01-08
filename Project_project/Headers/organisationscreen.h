#ifndef ORGANISATIONSCREEN_H
#define ORGANISATIONSCREEN_H

#include <QDialog>
#include "Headers/databaseinterface.h"
#include "Headers/addorgdialog.h"
#include "Headers/addansdialog.h"

namespace Ui {
class OrganisationScreen;
}

class OrganisationScreen : public QDialog
{
Q_OBJECT

public:
explicit OrganisationScreen(QWidget *parent = nullptr, DatabaseInterface* db = nullptr);
~OrganisationScreen();

private slots:
void on_addOrg_clicked ();

void on_remOrg_clicked ();

void on_addAns_clicked ();

void on_remAns_clicked ();

void on_OrgList_currentRowChanged (int currentRow);

void on_AnsprechpartnerTable_cellChanged (int row, int column);

void on_buttonBox_accepted ();

void on_buttonBox_rejected ();

private:
Ui::OrganisationScreen *ui;
DatabaseInterface* db;
int lastRow = 0;
void loadOrgList ();
void loadTableItems (int id);
};

#endif // ORGANISATIONSCREEN_H
