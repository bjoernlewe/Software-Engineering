#ifndef SINGINSCREEN_H
#define SINGINSCREEN_H

#include <QDialog>
#include <QDebug>
#include "Headers/databaseinterface.h"

namespace Ui {
class SingInScreen;
}

class SingInScreen : public QDialog
{
Q_OBJECT

public:
explicit SingInScreen(QWidget *parent = nullptr, DatabaseInterface* db = nullptr);
~SingInScreen();

private slots:

void on_radioStudent_clicked ();

void on_radioDozent_clicked ();

void on_SignIn_pressed ();

void on_Password1_textChanged (const QString &arg1);

void on_Password2_textChanged (const QString &arg1);

void on_Vorname_editingFinished ();

void on_Nachname_editingFinished ();

private:
Ui::SingInScreen *ui;
DatabaseInterface* db;
QString* typ;
QString* vorname;
QString* nachname;
QString* password;
};

#endif // SINGINSCREEN_H
