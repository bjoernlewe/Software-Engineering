#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QDialog>
#include "Headers/singinscreen.h"
#include <Headers/mainwindow.h>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QDialog
{
Q_OBJECT

public:
explicit LoginScreen(QWidget *parent = nullptr);
~LoginScreen();

private slots:
void on_SignIn_clicked ();
void showLogin ();

void on_LogIn_clicked ();

private:
Ui::LoginScreen *ui;
MainWindow* m;
};

#endif // LOGINSCREEN_H
