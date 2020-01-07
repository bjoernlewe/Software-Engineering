#include "Headers/insertprojectdialog.h"
#include "ui_insertprojectdialog.h"

InsertProjectDialog::InsertProjectDialog(QWidget *parent) :
        QDialog (parent),
        ui (new Ui::InsertProjectDialog)
{
        ui->setupUi (this);
}

InsertProjectDialog::~InsertProjectDialog()
{
        qDebug () << "InsertProjectDialog::~InsertProjectDialog()";
        delete ui;
}


