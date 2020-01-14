#include "Headers/loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget *parent, DatabaseInterface* db) :
        QDialog (parent),
        ui (new Ui::LoginScreen)
{
        ui->setupUi (this);
        this->m = static_cast<MainWindow*> (parent);
        if (db == nullptr) {
                this->db = new DatabaseInterface ();
        }
        else {
                this->db = db;
        }

        connect (m, &MainWindow::backToLogin, this, &LoginScreen::showLogin);
}

LoginScreen::~LoginScreen()
{
        delete ui;
}

void LoginScreen::on_SignIn_clicked ()
{
        SingInScreen signIn (this, db);

        this->hide ();

        signIn.exec ();
        this->show ();
}

void LoginScreen::showLogin ()
{
        this->show ();
        m->hide ();
}

void LoginScreen::on_LogIn_clicked ()
{
        if (checkIfUser (ui->VornameInput->text (), ui->NachnameInput->text (), ui->PasswordInput->text ())) {
                this->hide ();
                m->setType (type);
                m->showMaximized ();
                m->show ();
        }
        else{
                ui->VornameInput->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
                ui->NachnameInput->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
                ui->PasswordInput->setStyleSheet ("QLineEdit{"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-color: darkred;"
                        "}");
        }
}

bool LoginScreen::checkIfUser (const QString &vorname, const QString &nachname, const QString &password)
{
        bool userExists = false;

        //Übergangslösung, deckt nicht ab, falls es einen Dozenten und Studenten mit selben Namen gibt
        for (int i = 0; i < db->getStudentenverwaltung ()->length (); i++) {
                if (db->getStudentenverwaltung ()->at (i)->getVorname () == vorname) {
                        if (db->getStudentenverwaltung ()->at (i)->getNachname () == nachname) {
                                if (db->getStudentenverwaltung ()->at (i)->getPassword () == password) {
                                        userExists = true;
                                        type = "Student";
                                }
                        }
                }
        }

        for (int i = 0; i < db->getAnsprechVerwaltung ()->length (); i++) {
                if (db->getAnsprechVerwaltung ()->at (i)->getVorname () == vorname) {
                        if (db->getAnsprechVerwaltung ()->at (i)->getNachname () == nachname) {
                                if (db->getAnsprechVerwaltung ()->at (i)->getPassword () == password) {
                                        userExists = true;
                                        type = "Dozent";
                                }
                        }
                }
        }

        return userExists;
}

void LoginScreen::on_VornameInput_textChanged (const QString &arg1)
{
        Q_UNUSED (arg1)
        ui->VornameInput->setStyleSheet ("");
}

void LoginScreen::on_NachnameInput_textChanged (const QString &arg1)
{
        Q_UNUSED (arg1)
        ui->NachnameInput->setStyleSheet ("");
}

void LoginScreen::on_PasswordInput_textChanged (const QString &arg1)
{
        Q_UNUSED (arg1)
        ui->PasswordInput->setStyleSheet ("");
}
