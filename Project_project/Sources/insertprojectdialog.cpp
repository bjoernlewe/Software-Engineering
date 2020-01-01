#include "Headers/insertprojectdialog.h"
#include "ui_insertprojectdialog.h"

InsertProjectDialog::InsertProjectDialog(QWidget *parent, QStringList* ansprechpartner, QStringList* studenten, QStringList* org) :
        QDialog (parent),
        ui (new Ui::InsertProjectDialog)
{
        ui->setupUi (this);

        if (ansprechpartner == nullptr || studenten == nullptr || org == nullptr) {
                throw QString ("InsertProjectDialog::InsertProjectDialog() : not enough parameter");
        }


        this->ansprechpartner = ansprechpartner;
        this->studenten = studenten;
        this->organisation = org;

        QStringList justStudentName;
        justStudentName.append ("");
        for (int i = 0; i < this->studenten->length (); i++) {
                auto value = this->studenten->at (i).split (" ");
                justStudentName.append (value.at (2) + " " + value.at (3));
        }

        QStringList justAnsprName;
        justAnsprName.append ("");
        for (int i = 0; i < this->ansprechpartner->length (); i++) {
                auto value = this->ansprechpartner->at (i).split (" ");
                justAnsprName.append (value.at (2) + " " + value.at (3));
        }

        QStringList justOrgName;
        justOrgName.append ("");
        for (int i = 0; i < this->organisation->length (); i++) {
                auto value = this->organisation->at (i).split (" ");
                justOrgName.append (value.at (3));
        }


        ui->AnsprechpartnerCombo->addItems (justAnsprName);

        ui->OrganisationCombo->addItems (justOrgName);

        ui->StudentCombo1->addItems (justStudentName);
        ui->StudentCombo2->addItems (justStudentName);
        ui->StudentCombo3->addItems (justStudentName);
}

InsertProjectDialog::~InsertProjectDialog()
{
        qDebug () << "InsertProjectDialog::~InsertProjectDialog()";
        delete ui;
}

void InsertProjectDialog::on_ProNameLineEdit_editingFinished ()
{
        if (!(ui->ProNameLineEdit->text ().isNull () || ui->ProNameLineEdit->text ().isEmpty ())) {
                this->sendRequestFlag = true;
        }
}

void InsertProjectDialog::on_BeschreibungLineEdit_editingFinished ()
{
        if (!(ui->BeschreibungLineEdit->text ().isNull () || ui->BeschreibungLineEdit->text ().isEmpty ())) {
                this->sendRequestFlag = true;
        }
}

void InsertProjectDialog::on_HintergrundLineEdit_editingFinished ()
{
        if (!(ui->HintergrundLineEdit->text ().isNull () || ui->HintergrundLineEdit->text ().isEmpty ())) {
                this->sendRequestFlag = true;
        }
}

void InsertProjectDialog::on_buttonBox_accepted ()
{
        qDebug () << "InsertProjectDialog::on_buttonBox_accepted ()";
        if (this->sendRequestFlag) {
                qDebug () << ui->ProNameLineEdit->text ();
                qDebug () << ui->BeschreibungLineEdit->text ();
                qDebug () << ui->HintergrundLineEdit->text ();
                qDebug () << ((ui->AnsprechpartnerCombo->currentIndex () - 1 <= 0) ? "" : ansprechpartner->at (ui->AnsprechpartnerCombo->currentIndex () - 1));
                qDebug () << ((ui->StudentCombo1->currentIndex () <= 0) ? "" : studenten->at (ui->StudentCombo1->currentIndex () - 1));
                qDebug () << ((ui->StudentCombo2->currentIndex () <= 0) ? "" : studenten->at (ui->StudentCombo2->currentIndex () - 1));
                qDebug () << ((ui->StudentCombo3->currentIndex () <= 0) ? "" : studenten->at (ui->StudentCombo3->currentIndex () - 1));
                emit insertNew (ui->ProNameLineEdit->text (),
                                ui->BeschreibungLineEdit->text (),
                                ui->HintergrundLineEdit->text (),
                                ui->AnsprechpartnerCombo->currentIndex () <= 0 ? "" : ansprechpartner->at (ui->AnsprechpartnerCombo->currentIndex () - 1),
                                ui->StudentCombo1->currentIndex () <= 0 ? "" : studenten->at (ui->StudentCombo1->currentIndex () - 1),
                                ui->StudentCombo2->currentIndex () <= 0 ? "" : studenten->at (ui->StudentCombo2->currentIndex () - 1),
                                ui->StudentCombo3->currentIndex () <= 0 ? "" : studenten->at (ui->StudentCombo3->currentIndex () - 1));
        }
}

void InsertProjectDialog::on_AnsprechpartnerCombo_currentIndexChanged (int index)
{
        qDebug () << "InsertProjectDialog::on_AnsprechpartnerCombo_currentIndexChanged(" << index << ")";
        if (index > 0) {
                this->sendRequestFlag = true;
                ui->OrganisationCombo->setCurrentIndex (
                        this->ansprechpartner->at (index - 1).split (" ").at (1).toInt ()
                        );
        }
}

void InsertProjectDialog::on_StudentCombo1_currentIndexChanged (int index)
{
        qDebug () << "InsertProjectDialog::on_StudentCombo1_currentIndexChanged(" << index << ")";
        if (index > 0) {
                this->sendRequestFlag = true;
        }
}

void InsertProjectDialog::on_StudentCombo2_currentIndexChanged (int index)
{
        qDebug () << "InsertProjectDialog::on_StudentCombo2_currentIndexChanged(" << index << ")";
        if (index > 0) {
                this->sendRequestFlag = true;
        }
}

void InsertProjectDialog::on_StudentCombo3_currentIndexChanged (int index)
{
        qDebug () << "InsertProjectDialog::on_StudentCombo3_currentIndexChanged(" << index << ")";
        if (index > 0) {
                this->sendRequestFlag = true;
        }
}

void InsertProjectDialog::on_OrganisationCombo_currentIndexChanged (int index)
{
        qDebug () << "InsertProjectDialog::on_OrganisationCombo_currentIndexChanged (" << index << ")";
        if (index > 0) {
                this->sendRequestFlag = true;
        }
}
