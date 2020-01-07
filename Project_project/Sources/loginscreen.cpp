#include "Headers/loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget *parent) :
        QDialog (parent),
        ui (new Ui::LoginScreen)
{
        ui->setupUi (this);
        this->m = new MainWindow (parent);

        connect (m, &MainWindow::backToLogin, this, &LoginScreen::showLogin);
}

LoginScreen::~LoginScreen()
{
        delete ui;
}

void LoginScreen::on_SignIn_clicked ()
{
        SingInScreen signIn (this);

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
        this->hide ();
        m->showMaximized ();
        m->show ();
}
