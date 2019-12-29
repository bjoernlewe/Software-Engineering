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

void InsertProjectDialog::on_ProIDLineEdit_editingFinished ()
{
        if (!(ui->ProIDLineEdit->text ().isNull () || ui->ProIDLineEdit->text ().isEmpty ())) {
                this->sendRequestFlag = true;
        }
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

void InsertProjectDialog::on_AnsprechLineEdit_editingFinished ()
{
}

void InsertProjectDialog::on_StudentLineEdit_editingFinished ()
{
}

void InsertProjectDialog::on_buttonBox_accepted ()
{
        qDebug () << "void InsertProjectDialog::on_buttonBox_accepted ()";
        if (this->sendRequestFlag) {
                emit insertNew (ui->ProIDLineEdit->text ().toInt (), ui->ProNameLineEdit->text (),
                                ui->BeschreibungLineEdit->text (), ui->HintergrundLineEdit->text (), nullptr, nullptr);
        }
}
