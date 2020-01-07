#include "Headers/singinscreen.h"
#include "ui_singinscreen.h"

SingInScreen::SingInScreen(QWidget *parent) :
        QDialog (parent),
        ui (new Ui::SingInScreen)
{
        ui->setupUi (this);
}

SingInScreen::~SingInScreen()
{
        delete ui;
}
