#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow (parent)
        , ui (new Ui::MainWindow)
{
        ui->setupUi (this);
        setRole ("Student");
        connect (this, &MainWindow::onUpdate, this, &MainWindow::refresh);
        emit onUpdate ();
        ui->stackedWidget->addWidget (dbInterface.getStuView ());
        ui->stackedWidget->addWidget (dbInterface.getProfView ());
//        this->showMaximized ();
        qDebug () << ui->stackedWidget->children ();
}

MainWindow::~MainWindow()
{
        delete ui;
}


void MainWindow::on_actionStudent_triggered ()
{
        setRole ("Student");
        emit onUpdate ();
}

void MainWindow::on_actionDozent_triggered ()
{
        setRole ("Dozent");
        emit onUpdate ();
}

QString MainWindow::getRole () const
{
        return role;
}

void MainWindow::setRole (const QString &value)
{
        role = value;
}

void MainWindow::on_insertProject_clicked ()
{
        InsertProjectDialog dialog (this);

        dialog.showMaximized ();
        connect (&dialog, &InsertProjectDialog::insertNew, this, &MainWindow::newInsert);
        dialog.exec ();
}

void MainWindow::refresh ()
{
        qDebug () << "Before: " << ui->stackedWidget->currentWidget ();
//        dbInterface.refresh ();
        if (getRole () == "Student") {
                ui->insertProject->setEnabled (true);
                ui->insertProject->setHidden (false);
                ui->MarkToEdit->setHidden (true);
                ui->MarkToEdit->setEnabled (false);
                ui->stackedWidget->setCurrentIndex (0);
        }
        else{
                ui->insertProject->setHidden (true);
                ui->insertProject->setEnabled (false);
                ui->MarkToEdit->setHidden (false);
                ui->MarkToEdit->setEnabled (true);
                ui->stackedWidget->setCurrentIndex (1);
        }
        qDebug () << "After: " << ui->stackedWidget->currentWidget ();
        ui->stackedWidget->update ();
        this->update ();
}

void MainWindow::newInsert (int projID, const QString &projName, const QString &projBesc, const QString &projHinter, const QString &projAnspr, const QString &projStudent)
{
        qDebug () << "MainWindow::newInsert()";
        qDebug () << "Projekt ID: " << projID;
        qDebug () << "Projektname: " << projName;
        qDebug () << "Projekt Beschreibung: " << projBesc;
        qDebug () << "Projekt Hintergrund: " << projHinter;
        qDebug () << "Ansprechpartner: " << projAnspr;
        qDebug () << "Studenten: " << projStudent;
        dbInterface.newEntry (projID, projName, projBesc, projHinter, projAnspr, projStudent);
}
