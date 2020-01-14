#include "Headers/signinscreen.h"
#include "ui_singinscreen.h"

SingInScreen::SingInScreen(QWidget *parent, DatabaseInterface* db) :
        QDialog (parent),
        ui (new Ui::SingInScreen)
{
        ui->setupUi (this);
        if (db == nullptr) {
                this->db = new DatabaseInterface ();
        }
        else {
                this->db = db;
        }
        typ = new QString ();
        vorname = new QString ();
        nachname = new QString ();
        password = new QString ();
}

SingInScreen::~SingInScreen()
{
        delete ui;
}



void SingInScreen::on_radioStudent_clicked ()
{
        *typ = "Student";
        ui->radioDozent->setStyleSheet ("");
        ui->radioStudent->setStyleSheet ("");
}

void SingInScreen::on_radioDozent_clicked ()
{
        *typ = "Dozent";
        ui->radioDozent->setStyleSheet ("");
        ui->radioStudent->setStyleSheet ("");
}

void SingInScreen::on_SignIn_pressed ()
{
        if (typ->isNull () || typ->isEmpty ()) {
                qDebug () << "Keinen Typen gewählt";
                ui->radioDozent->setStyleSheet ("QRadioButton{"
                        "color: red;"
                        "}");
                ui->radioStudent->setStyleSheet ("QRadioButton{"
                        "color: red;"
                        "}");
        }

        if (vorname->isNull () || vorname->isEmpty ()) {
                qDebug () << "Keinen Nutzernamen eingegeben";
                ui->Vorname->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
        }

        if (nachname->isNull () || nachname->isEmpty ()) {
                qDebug () << "Keinen Nutzernamen eingegeben";
                ui->Nachname->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
        }

        if (password->isNull () || password->isEmpty ()) {
                qDebug () << "Kein Password eingegeben";
                ui->Password1->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
                ui->Password2->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
        }

        if (ui->Password1->text () == ui->Password2->text ()
            && ui->Password1->text () != ""
            && ui->Vorname->text () != ""
            && ui->Nachname->text () != ""
            && *typ != "") {
                qDebug () << *typ;
                ui->Password1->setStyleSheet ("");
                ui->Password2->setStyleSheet ("");
                *vorname = ui->Vorname->text ();
                *nachname = ui->Nachname->text ();
                *password = ui->Password1->text ();
                db->signIn (*this->vorname, *this->nachname, *this->password, *this->typ);
                this->accept ();
        }
        else{
                ui->Password1->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
                ui->Password2->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
        }
}


void SingInScreen::on_Password1_textChanged (const QString &arg1)
{
        Q_UNUSED (arg1)
        ui->Password1->setStyleSheet ("");
}

void SingInScreen::on_Password2_textChanged (const QString &arg1)
{
        qDebug () << ui->Password1->text () << " == " << ui->Password2->text ();
        if (arg1 == ui->Password1->text ()) {
                ui->Password2->setStyleSheet ("");
        }
        else {
                ui->Password2->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
        }
}



void SingInScreen::on_Vorname_editingFinished ()
{
        *vorname = ui->Vorname->text ();
        ui->Vorname->setStyleSheet ("");
}

void SingInScreen::on_Nachname_editingFinished ()
{
        *nachname = ui->Nachname->text ();
        ui->Nachname->setStyleSheet ("");
}
