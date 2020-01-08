#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow (parent)
        , ui (new Ui::MainWindow)
{
        ui->setupUi (this);
        emit onUpdate ();
}

MainWindow::~MainWindow()
{
        delete ui;
}

void MainWindow::on_actionLog_Out_triggered ()
{
        emit backToLogin ();
}

void MainWindow::on_actionGruppe_triggered ()
{
        InsertProjectDialog i;

        i.showMaximized ();
        this->hide ();
        i.exec ();
        this->show ();
}

void MainWindow::on_actionOrganisation_triggered ()
{
        OrganisationScreen o (this, &dbInterface);

        o.showMaximized ();

        this->hide ();
        o.exec ();
        this->show ();
}
