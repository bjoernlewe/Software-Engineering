#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DatabaseInterface* db)
        : QMainWindow (parent)
        , ui (new Ui::MainWindow)
{
        ui->setupUi (this);
        if (db == nullptr) {
                this->dbInterface = new DatabaseInterface ();
        }
        else{
                this->dbInterface = db;
        }
        emit onUpdate ();
}

MainWindow::~MainWindow()
{
        delete ui;
}

QString MainWindow::getType () const
{
        return type;
}

void MainWindow::setType (const QString &value)
{
        type = value;
}

void MainWindow::on_actionLog_Out_triggered ()
{
        emit backToLogin ();
}

void MainWindow::on_actionGruppe_triggered ()
{
        InsertProjectDialog i (this, dbInterface);

        i.showMaximized ();
        this->hide ();
        i.exec ();
        this->show ();
}

void MainWindow::on_actionOrganisation_triggered ()
{
        OrganisationScreen o (this, dbInterface);

        o.showMaximized ();

        this->hide ();
        o.exec ();
        this->show ();
}
