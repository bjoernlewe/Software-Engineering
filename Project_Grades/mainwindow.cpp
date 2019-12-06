#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow (parent),
        ui (new Ui::MainWindow)
{
        try {
                qDebug () << "MainWindow::MainWindow() called";
                ui->setupUi (this);
                kolloquium = new Kolloquium ("Kolloquium", 0);
                kolloquiumBuffer = new Kolloquium ("kollBuffer", 0);

                exam = new FinalExam ("Abschlussarbeit", 0);
                examBuffer = new FinalExam ("examBuffer", 0);

                connect (this, &MainWindow::onUpdate, this, [this] {
                        calculateAverage ();
                        ui->averageGrade->setNum (average);
                });

                QStringList labelList;
                //TableView Header
                labelList.append ("Semester");
                labelList.append ("Fach");
                labelList.append ("Note");
                labelList.append ("Credits");
                ui->gradeTableOverview->setHorizontalHeaderLabels (labelList);
                this->update ();
                emit onUpdate ();

//        this->showMaximized ();
        } catch (QString string) {
                qDebug () << string;
        }
}

MainWindow::~MainWindow()
{
        qDebug () << "MainWindow::~MainWindow() called";
        delete ui;
}

void MainWindow::calculateAverage ()
{
        float allGradeTimesCredits = 0.0;
        int allCredits = 0;

        for (int i = 0; i < subjectList.length (); i++) {
                allGradeTimesCredits += (subjectList.at (i).getGradeList ().last ().getGrade () * subjectList.at (i).getCredits ());
                allCredits += subjectList.at (i).getCredits ();
        }
        if (!exam->getGradeList ().isEmpty ()) {
                allGradeTimesCredits += (exam->getGradeList ().last ().getGrade () * exam->getCredits ());
        }

        allCredits += exam->getCredits ();

        if (allCredits == 0) {
                average = 0;
        }
        else{
                average = allGradeTimesCredits / allCredits;
        }
}


void MainWindow::on_buttonToExamsDialog_clicked ()
{
        qDebug () << "MainWindow::on_buttonToExamsDialog_clicked() called";
        QDialog* examsDialog = new QDialog ();

        examsDialog->setWindowTitle ("Abschlussarbeit");
        QGridLayout* grid = new QGridLayout ();

        //Exams Dialog Labels
        QLabel* examsLabel = new QLabel ("Abschlussarbeit");
        QLabel* markLabel = new QLabel ("Note");
        QLabel* creditsLabel = new QLabel ("Credits");
        QLabel* kolloquiumLabel = new QLabel ("Kolloquium");

        QLineEdit* examEdit = new QLineEdit ();
        QLineEdit* examMarkEdit = new QLineEdit ();
        QLineEdit* examCreditEdit = new QLineEdit ();
        QLineEdit* kolloquiumEdit = new QLineEdit ();
        QLineEdit* kolloquiumMarkEdit = new QLineEdit ();
        QLineEdit* kolloquiumCreditEdit = new QLineEdit ();

        examBuffer->setName (exam->getName ());
        kolloquiumBuffer->setName (kolloquium->getName ());

        examEdit->setText (exam->getName ());
        examMarkEdit->insert (exam->getGradeListTxt ());
        examCreditEdit->setText (QString::number (exam->getCredits ()));

        kolloquiumEdit->setText (kolloquium->getName ());
        kolloquiumMarkEdit->insert (kolloquium->getGradeListTxt ());
        kolloquiumCreditEdit->setText (QString::number (kolloquium->getCredits ()));


        grid->addWidget (examsLabel, 0, 0);
        grid->addWidget (markLabel, 0, 1);
        grid->addWidget (creditsLabel, 0, 2);
        grid->addWidget (examEdit, 1, 0);
        grid->addWidget (examMarkEdit, 1, 1);
        grid->addWidget (examCreditEdit, 1, 2);
        grid->addWidget (kolloquiumLabel, 2, 0);
        grid->addWidget (kolloquiumEdit, 4, 0);
        grid->addWidget (kolloquiumMarkEdit, 4, 1);
        grid->addWidget (kolloquiumCreditEdit, 4, 2);

        QPushButton* okButton = new QPushButton ("Ok");
        QPushButton* cancelButton = new QPushButton ("Abbrechen");
        grid->addWidget (okButton, 5, 1);
        grid->addWidget (cancelButton, 5, 2);

        connect (examEdit, &QLineEdit::editingFinished, this, [this, examEdit] {
                this->examBuffer->setName (examEdit->text ());
        });

        connect (examMarkEdit, &QLineEdit::editingFinished, this, [this, examMarkEdit] {
                this->examBuffer->addGrade (Grade (examMarkEdit->text ().toFloat ()));
        });

        connect (examCreditEdit, &QLineEdit::editingFinished, this, [this, examCreditEdit] {
                this->examBuffer->setCredits (examCreditEdit->text ().toInt ());
        });

        connect (kolloquiumEdit, &QLineEdit::editingFinished, this, [this, kolloquiumEdit] {
                this->kolloquiumBuffer->setName (kolloquiumEdit->text ());
        });

        connect (kolloquiumMarkEdit, &QLineEdit::editingFinished, this, [this, kolloquiumMarkEdit] {
                this->kolloquiumBuffer->addGrade (Grade (kolloquiumMarkEdit->text ().toFloat ()));
        });

        connect (kolloquiumCreditEdit, &QLineEdit::editingFinished, this, [this, kolloquiumCreditEdit] {
                this->kolloquiumBuffer->setCredits (kolloquiumCreditEdit->text ().toInt ());
        });

        connect (okButton, &QPushButton::clicked, this, [this, examsDialog] {
                this->saveDialog (examsDialog);
        });

        connect (cancelButton, &QPushButton::clicked, this, [this, examsDialog] {
                this->exitWindowSlot (examsDialog);
        });

        examsDialog->setLayout (grid);
        examsDialog->open ();
}

void MainWindow::on_actionAddNewSubject_triggered ()
{
        qDebug () << "MainWindow::on_actionAddNewSubject_triggered() called";
        ui->gradeTableOverview->insertRow (0);
        this->update ();
        emit onUpdate ();
}

void MainWindow::on_actionExit_triggered ()
{
        qDebug () << "MainWindow::on_actionExit_triggered() called";
        this->close ();
}

void MainWindow::closeEvent (QCloseEvent *e)
{
        qDebug () << "MainWindow::closeEvent() called";
        e->ignore ();
        QMessageBox msgbox;

        msgbox.setWindowTitle ("Exit?");
        msgbox.setText ("Möchtest du die Anwendung wirklich schließen?");
        msgbox.setTextFormat (Qt::TextFormat::AutoText);
        msgbox.setIcon (QMessageBox::Icon::Warning);
        msgbox.addButton (QMessageBox::Yes);
        msgbox.addButton (QMessageBox::No);
        if (msgbox.exec () == QMessageBox::Yes) {
                QCoreApplication::quit ();
        }
}

void MainWindow::saveDialog (QWidget* widget)
{
        qDebug () << "MainWindow::save() called";
        exam->setName (examBuffer->getName ());
        exam->setGradeList (examBuffer->getGradeList ());
        exam->setCredits (examBuffer->getCredits ());

        kolloquium->setName (kolloquiumBuffer->getName ());
        kolloquium->setGradeList (kolloquiumBuffer->getGradeList ());
        kolloquium->setCredits (kolloquiumBuffer->getCredits ());

        subjectList = subjectBufferList;
        emit onUpdate ();
        widget->close ();
}

void MainWindow::exitWindowSlot (QDialog* window)
{
        qDebug () << "MainWindow::exitSlot() called";
        QMessageBox msgbox;

        msgbox.setWindowTitle ("Änderungen verwerfen?");
        msgbox.setText ("Möchtest sie die Änderungen wirklich verwerfen?");
        msgbox.setTextFormat (Qt::TextFormat::AutoText);
        msgbox.setIcon (QMessageBox::Icon::Warning);
        msgbox.addButton (QMessageBox::Yes);
        msgbox.addButton (QMessageBox::No);
        if (msgbox.exec () == QMessageBox::Yes) {
                window->close ();
        }
}


void MainWindow::on_gradeTableOverview_itemDoubleClicked (QTableWidgetItem *item)
{
        qDebug () << "MainWindow::on_gradeTableOverview_itemDoubleClicked () called";
        QMessageBox* detailedSubjectInfo = new QMessageBox ();

        detailedSubjectInfo->addButton (QMessageBox::Ok);
        detailedSubjectInfo->addButton (QMessageBox::Cancel);


        if (detailedSubjectInfo->exec () == QMessageBox::Ok) {
        }
}
