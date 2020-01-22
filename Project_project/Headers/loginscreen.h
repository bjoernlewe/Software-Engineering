#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QDialog>
#include "Headers/signinscreen.h"
#include <Headers/mainwindow.h>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QDialog
{
Q_OBJECT

public:
explicit LoginScreen(QWidget *parent = nullptr, DatabaseInterface* db = nullptr);
~LoginScreen();

private slots:
void on_SignIn_clicked ();
void showLogin ();

void on_LogIn_clicked ();

void on_VornameInput_textChanged (const QString &arg1);

void on_NachnameInput_textChanged (const QString &arg1);

void on_PasswordInput_textChanged (const QString &arg1);

private:
bool checkIfUser (const QString& vorname, const QString& nachname, const QString& password);
int getIDFromVerwaltung (const QString& vorname, const QString& nachname, const QString& password, const QString& type);
QString type;
DatabaseInterface* db;
Ui::LoginScreen *ui;
MainWindow* m;
};

#endif // LOGINSCREEN_H
