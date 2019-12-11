#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow (parent),
        ui (new Ui::MainWindow)
{
        try {
                qDebug () << "MainWindow::MainWindow() called";
                ui->setupUi (this);

                constraint = new QList<float>();
                constraint->append (1.0f);
                constraint->append (1.3f);
                constraint->append (1.7f);
                constraint->append (2.0f);
                constraint->append (2.3f);
                constraint->append (2.7f);
                constraint->append (3.0f);
                constraint->append (3.3f);
                constraint->append (3.7f);
                constraint->append (4.0f);
                constraint->append (5.0f);

                lastRow = -1;

                subjectList = new QList<Subject>();
                subjectBufferList = new QList<Subject>();

                kolloquium = new Kolloquium ("Kolloquium", 0);
                kolloquiumBuffer = new Kolloquium ("kollBuffer", 0);

                exam = new FinalExam ("Abschlussarbeit", 0);
                examBuffer = new FinalExam ("examBuffer", 0);

                mapper = new QDataWidgetMapper ();
                mapper->setModel (ui->gradeTableOverview->model ());

                valueListBuffer = new QList<QString>();

                connect (this, &MainWindow::onUpdate, this, [this] {
                        calculateAverage ();
                        ui->averageGrade->setNum (average);
                });

                //TableView Header
                columnLabels = new QStringList ();
                columnLabels->append ("Semester");
                columnLabels->append ("Fach");
                columnLabels->append ("Note");
                columnLabels->append ("Credits");
                ui->gradeTableOverview->setHorizontalHeaderLabels (*columnLabels);


                ui->gradeTableOverview->model ();
                this->update ();
                emit onUpdate ();

//        this->showMaximized ();
        } catch (QString string) {
                qDebug () << "Exception Caught in MainWindow::MainWindow(): " << string;
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

        for (int i = 0; i < subjectList->length (); i++) {
                float grade = subjectList->at (i).getLastGrade ();
                if (!(grade == 5.0f || grade == -1.f)) {
                        allGradeTimesCredits += grade * subjectList->at (i).getCredits ();
                        allCredits += subjectList->at (i).getCredits ();
                }
        }
        if (!(exam->getLastGrade () == 5.0f || exam->getLastGrade () == -1.f)) {
                allGradeTimesCredits += (exam->getLastGrade () * exam->getCredits ());
                allCredits += exam->getCredits ();
        }

        if (allCredits == 0) {
                average = 0;
        }
        else{
                average = allGradeTimesCredits / allCredits;
        }
}


void MainWindow::on_buttonToExamsDialog_clicked ()
{
        try {
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
                examBuffer->setGrade1 (exam->getGrade1 ());
                examBuffer->setGrade2 (exam->getGrade2 ());
                examBuffer->setGrade3 (exam->getGrade3 ());
                examBuffer->setCredits (exam->getCredits ());

                kolloquiumBuffer->setName (kolloquium->getName ());
                kolloquiumBuffer->setGrade1 (kolloquium->getGrade1 ());
                kolloquiumBuffer->setGrade2 (kolloquium->getGrade2 ());
                kolloquiumBuffer->setGrade3 (kolloquium->getGrade3 ());
                kolloquiumBuffer->setCredits (kolloquium->getCredits ());

                examEdit->setText (exam->getName ());
                examMarkEdit->setText (exam->getGradeListTxt ());
                examCreditEdit->setText (QString::number (exam->getCredits ()));



                kolloquiumEdit->setText (kolloquium->getName ());
                kolloquiumMarkEdit->setText (kolloquium->getGradeListTxt ());
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
                        auto examArray = examMarkEdit->text ().split (",");
                        if (examArray.length () == 1) {
                                if (checkConstraint (examArray.at (0).toFloat ())) {
                                        examBuffer->setGrade1 (Grade (examArray.at (0).toFloat ()));
                                        examBuffer->setGrade2 (Grade ());
                                        examBuffer->setGrade3 (Grade ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + examArray.at (0) + " used.";
                                }
                        }
                        else {
                                if (examArray.length () == 2) {
                                        if (checkConstraint (examArray.at (1).toFloat ())) {
                                                examBuffer->setGrade2 (Grade (examArray.at (1).toFloat ()));
                                                examBuffer->setGrade3 (Grade ());
                                        }
                                        else{
                                                qDebug () << "Invalid Grade " + examArray.at (1) + " used.";
                                        }
                                }
                                else {
                                        if (examArray.length () == 3) {
                                                if (checkConstraint (examArray.at (2).toFloat ())) {
                                                        examBuffer->setGrade3 (Grade (examArray.at (2).toFloat ()));
                                                }
                                                else {
                                                        qDebug () << "Invalid Grade " + examArray.at (2) + " used.";
                                                }
                                        }
                                }
                        }
                });

                connect (examCreditEdit, &QLineEdit::editingFinished, this, [this, examCreditEdit] {
                        this->examBuffer->setCredits (examCreditEdit->text ().toInt ());
                });

                connect (kolloquiumEdit, &QLineEdit::editingFinished, this, [this, kolloquiumEdit] {
                        this->kolloquiumBuffer->setName (kolloquiumEdit->text ());
                });

                connect (kolloquiumMarkEdit, &QLineEdit::editingFinished, this, [this, kolloquiumMarkEdit] {
                        auto kollArray = kolloquiumMarkEdit->text ().split (",");
                        if (kollArray.length () == 1) {
                                if (checkConstraint (kollArray.at (0).toFloat ())) {
                                        kolloquiumBuffer->setGrade1 (Grade (kollArray.at (0).toFloat ()));
                                        kolloquiumBuffer->setGrade2 (Grade ());
                                        kolloquiumBuffer->setGrade3 (Grade ());
                                }
                                else {
                                        qDebug () << "Invalid Grade " + kollArray.at (0) + " used.";
                                }
                        }
                        else {
                                if (kollArray.length () == 2) {
                                        if (checkConstraint (kollArray.at (1).toFloat ())) {
                                                kolloquiumBuffer->setGrade2 (Grade (kollArray.at (1).toFloat ()));
                                                kolloquiumBuffer->setGrade3 (Grade ());
                                        }
                                        else {
                                                qDebug () << "Invalid Grade " + kollArray.at (1) + " used.";
                                        }
                                }
                                else {
                                        if (kollArray.length () == 3) {
                                                if (checkConstraint (kollArray.at (2).toFloat ())) {
                                                        kolloquiumBuffer->setGrade3 (Grade (kollArray.at (2).toFloat ()));
                                                }
                                                else {
                                                        qDebug () << "Invalid Grade " + kollArray.at (2) + " used.";
                                                }
                                        }
                                }
                        }
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
        } catch (QString exception) {
                qDebug () << "Exception caught in MainWindow::on_buttonToExamsDialog_clicked(): " << exception;
        }
}

void MainWindow::on_actionAddNewSubject_triggered ()
{
        try {
                qDebug () << "MainWindow::on_actionAddNewSubject_triggered() called";
                QDialog* createNewDialog = new QDialog ();
                QGridLayout* grid = new QGridLayout ();
                createNewDialog->setWindowTitle ("Neues Fach");

                QLabel* semesterLabel = new QLabel ("Semester");
                QLabel* subjectLabel = new QLabel ("Fach");
                QLabel* gradesLabel = new QLabel ("Noten");
                QLabel* creditsLabel = new QLabel ("Credits");

                QLineEdit* semesterEdit = new QLineEdit ();
                QLineEdit* subjectEdit = new QLineEdit ();
                QLineEdit* gradesEdit = new QLineEdit ();
                QLineEdit* creditsEdit = new QLineEdit ();

                QPushButton* okButton = new QPushButton ("Ok");
                QPushButton* cancelButton = new QPushButton ("Abbrechen");

                grid->addWidget (semesterLabel, 0, 0);
                grid->addWidget (semesterEdit, 0, 1);

                grid->addWidget (subjectLabel, 1, 0);
                grid->addWidget (subjectEdit, 1, 1);

                grid->addWidget (gradesLabel, 2, 0);
                grid->addWidget (gradesEdit, 2, 1);
                grid->addWidget (creditsLabel, 4, 0);
                grid->addWidget (creditsEdit, 4, 1);

                grid->addWidget (okButton);
                grid->addWidget (cancelButton);

                createNewDialog->setLayout (grid);

                Subject* newSubject = new Subject ("Default", 0);
                connect (semesterEdit, &QLineEdit::editingFinished, this, [semesterEdit, newSubject] {
                        newSubject->setSemester (semesterEdit->text ().toInt ());
                });
                connect (subjectEdit, &QLineEdit::editingFinished, this, [subjectEdit, newSubject] {
                        newSubject->setName (subjectEdit->text ());
                });
                connect (gradesEdit, &QLineEdit::editingFinished, this, [this, gradesEdit, newSubject] {
                        foreach (auto gradeTxt, gradesEdit->text ().split (",")) {
                                if (checkConstraint (gradeTxt.toFloat ())) {
                                        newSubject->addGrade (Grade (gradeTxt.toFloat ()));
                                }
                                else{
                                        qDebug () << "Invalid Grade " + gradeTxt + " used.";
                                }
                        }
                });
                connect (creditsEdit, &QLineEdit::editingFinished, this, [creditsEdit, newSubject] {
                        newSubject->setCredits (creditsEdit->text ().toInt ());
                });


                connect (okButton, &QPushButton::clicked, this, [this, createNewDialog, newSubject, semesterEdit, subjectEdit, gradesEdit, creditsEdit] {
                        if (!(semesterEdit->text ().isNull () || semesterEdit->text ().isEmpty () ||
                              subjectEdit->text ().isNull () || subjectEdit->text ().isEmpty () ||
                              gradesEdit->text ().isNull () || gradesEdit->text ().isEmpty () ||
                              creditsEdit->text ().isNull () || creditsEdit->text ().isEmpty ())) {
                                subjectList->append (*newSubject);
                                mapSubjectsToTableView ();
                                this->update ();
                                createNewDialog->close ();
                        }
                        else{
                                delete newSubject;
                                this->exitWindowSlot (createNewDialog);
                        }
                });

                connect (cancelButton, &QPushButton::clicked, this, [this, createNewDialog, newSubject] {
                        delete newSubject;
                        this->exitWindowSlot (createNewDialog);
                });

                createNewDialog->open ();
                this->update ();
                emit onUpdate ();
        } catch (QString exception) {
                qDebug () << "Exception caught in MainWindow::on_actionAddNewSubject_triggered (): " << exception;
        }
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
        try {
                qDebug () << "MainWindow::save() called";
                exam->setName (examBuffer->getName ());
                exam->setGrade1 (examBuffer->getGrade1 ());
                exam->setGrade2 (examBuffer->getGrade2 ());
                exam->setGrade3 (examBuffer->getGrade3 ());
                exam->setCredits (examBuffer->getCredits ());

                kolloquium->setName (kolloquiumBuffer->getName ());
                kolloquium->setGrade1 (kolloquiumBuffer->getGrade1 ());
                kolloquium->setGrade2 (kolloquiumBuffer->getGrade2 ());
                kolloquium->setGrade3 (kolloquiumBuffer->getGrade3 ());
                kolloquium->setCredits (kolloquiumBuffer->getCredits ());

                for (int i = 0; i < valueListBuffer->length (); i++) {
                        mapper->model ()->setData (mapper->model ()->index (lastRow, i), valueListBuffer->at (i));
                }

                valueListBuffer->clear ();

                emit onUpdate ();
                widget->close ();
        } catch (QString exception) {
                qDebug () << "Exception caught in MainWindow::saveDialog(): " << exception;
        }
}

void MainWindow::exitWindowSlot (QDialog* window)
{
        qDebug () << "MainWindow::exitSlot() called";
        QMessageBox msgbox;

        msgbox.setWindowTitle ("Änderungen verwerfen?");
        msgbox.setText ("Möchtest Sie die Änderungen wirklich verwerfen?");
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
        try {
                qDebug () << "MainWindow::on_gradeTableOverview_itemDoubleClicked () called";
                QList<QString>* valueList = new QList<QString>();
                lastRow = item->row ();
                for (int colIndex = 0; colIndex < mapper->model ()->columnCount (); colIndex++) {
                        valueList->insert (colIndex, mapper->model ()->index (lastRow, colIndex).data ().toString ());
                }

                Subject* subject = new Subject (valueList->at (1), valueList->at (3).toInt ());
                subject->setSemester (valueList->at (0).toInt ());
                foreach (auto gradeTxt, valueList->at (2).split (",")) {
                        subject->addGrade (Grade (gradeTxt.toFloat ()));
                }

                QDialog* detailedSubjectInfo = new QDialog ();
                detailedSubjectInfo->setWindowTitle (subject->getName ());
                QGridLayout* grid = new QGridLayout ();

                QLabel* semester = new QLabel ("Semester");
                QLabel* grades = new QLabel ("Noten");
                QLabel* credits = new QLabel ("Credits");


                QLineEdit* semesterEdit = new QLineEdit ();
                QLineEdit* grade1Edit = new QLineEdit ();
                QLineEdit* grade2Edit = new QLineEdit ();
                QLineEdit* grade3Edit = new QLineEdit ();
                QLineEdit* creditsEdit = new QLineEdit ();

                semesterEdit->setText (QString::number (subject->getSemester ()));
                grade1Edit->setText (subject->getGrade1 ().getGrade () >= 0 ? QString::number (subject->getGrade1 ().getGrade ()) : "");
                grade2Edit->setText (subject->getGrade2 ().getGrade () >= 0 ? QString::number (subject->getGrade2 ().getGrade ()) : "");
                grade3Edit->setText (subject->getGrade3 ().getGrade () >= 0 ? QString::number (subject->getGrade3 ().getGrade ()) : "");
                creditsEdit->setText (QString::number (subject->getCredits ()));

                grid->addWidget (semester, 0, 0);
                grid->addWidget (semesterEdit, 0, 1);

                grid->addWidget (grades, 1, 0);
                grid->addWidget (grade1Edit, 1, 1);
                grid->addWidget (grade2Edit, 2, 1);
                grid->addWidget (grade3Edit, 3, 1);

                grid->addWidget (credits, 4, 0);
                grid->addWidget (creditsEdit, 4, 1);

                replaceOrInsert (0, semesterEdit->text ());
                replaceOrInsert (1, detailedSubjectInfo->windowTitle ());

                QList<QString> list;
                list.append (grade1Edit->text ());
                list.append (grade2Edit->text ());
                list.append (grade3Edit->text ());
                replaceOrInsert (2, createStringList (list));

                QPushButton* okButton = new QPushButton ("OK");
                QPushButton* cancelButton = new QPushButton ("Abbrechen");

                connect (semesterEdit, &QLineEdit::editingFinished, this, [this, semesterEdit] {
                        try {
                                replaceOrInsert (0, semesterEdit->text ());
                        } catch (QString exception) {
                                qDebug () << exception;
                        }
                });

                connect (grade1Edit, &QLineEdit::editingFinished, this, [this, grade1Edit, grade2Edit, grade3Edit] {
                        try {
                                QList<QString> list;
                                if (checkConstraint (grade1Edit->text ().toFloat ())) {
                                        list.append (grade1Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade1Edit->text () + " used";
                                }
                                if (checkConstraint (grade2Edit->text ().toFloat ())) {
                                        list.append (grade2Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade2Edit->text () + " used";
                                }
                                if (checkConstraint (grade3Edit->text ().toFloat ())) {
                                        list.append (grade3Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade3Edit->text () + " used";
                                }
                                replaceOrInsert (2, createStringList (list));
                        } catch (QString exception) {
                                qDebug () << exception;
                        }
                });

                connect (grade2Edit, &QLineEdit::editingFinished, this, [this, grade1Edit, grade2Edit, grade3Edit] {
                        try {
                                QList<QString> list;
                                if (checkConstraint (grade1Edit->text ().toFloat ())) {
                                        list.append (grade1Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade1Edit->text () + " used";
                                }
                                if (checkConstraint (grade2Edit->text ().toFloat ())) {
                                        list.append (grade2Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade2Edit->text () + " used";
                                }
                                if (checkConstraint (grade3Edit->text ().toFloat ())) {
                                        list.append (grade3Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade3Edit->text () + " used";
                                }
                                replaceOrInsert (2, createStringList (list));
                        } catch (QString exception) {
                                qDebug () << exception;
                        }
                });

                connect (grade3Edit, &QLineEdit::editingFinished, this, [this, grade1Edit, grade2Edit, grade3Edit] {
                        try {
                                QList<QString> list;
                                if (checkConstraint (grade1Edit->text ().toFloat ())) {
                                        list.append (grade1Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade1Edit->text () + " used";
                                }
                                if (checkConstraint (grade2Edit->text ().toFloat ())) {
                                        list.append (grade2Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade2Edit->text () + " used";
                                }
                                if (checkConstraint (grade3Edit->text ().toFloat ())) {
                                        list.append (grade3Edit->text ());
                                }
                                else{
                                        qDebug () << "Invalid Grade " + grade3Edit->text () + " used";
                                }
                                replaceOrInsert (2, createStringList (list));
                        } catch (QString exception) {
                                qDebug () << exception;
                        }
                });

                connect (creditsEdit, &QLineEdit::editingFinished, this, [this, creditsEdit] {
                        try {
                                replaceOrInsert (3, creditsEdit->text ());
                        } catch (QString exception) {
                                qDebug () << exception;
                        }
                });

                connect (okButton, &QPushButton::clicked, this, [this, item, detailedSubjectInfo, subject] {
                        subjectList->replace (item->row (), *subject);
                        this->saveDialog (detailedSubjectInfo);
                });

                connect (cancelButton, &QPushButton::clicked, this, [this, detailedSubjectInfo] {
                        this->exitWindowSlot (detailedSubjectInfo);
                });

                grid->addWidget (okButton, 5, 2);
                grid->addWidget (cancelButton, 5, 3);

                detailedSubjectInfo->setLayout (grid);

                detailedSubjectInfo->open ();
        } catch (QString string) {
                qDebug () << "Exception caught in MainWindow::on_gradeTableOverview_itemDoubleClicked(): " << string;
        }
}

void MainWindow::replaceOrInsert (int index, const QString &data)
{
        qDebug () << "MainWindow::replaceOrInsert()";
        qDebug () << valueListBuffer->length ();
        if (valueListBuffer->length () == index) {
                valueListBuffer->insert (index, data);
        }
        else if (valueListBuffer->length () < index) {
                throw QString ("MainWindow::replaceOrInsert() : Out of Bounds: " + QString::number (index));
        }
        else{
                valueListBuffer->replace (index, data);
        }
}

bool MainWindow::checkConstraint (float value)
{
        for (int i = 0; i < constraint->length (); i++) {
                if (value == constraint->at (i)) {
                        return true;
                }
        }
        return false;
}

QLineEdit* MainWindow::changeToWarningColor (QLineEdit *edit)
{
        QColor color (Qt::GlobalColor::red);
        QGraphicsColorizeEffect effect;

        effect.setColor (color);
        edit->setGraphicsEffect (&effect);
        return edit;
}

QString MainWindow::createStringList (QList<QString> list)
{
        QString returnString;

        for (int i = 0; i < list.length (); i++) {
                if (i == list.length () - 1 || list.at (i + 1).isEmpty ()) {
                        returnString.append (list.at (i));
                }
                else {
                        returnString.append (list.at (i));
                        returnString.append (",");
                }
        }
        return returnString;
}

void MainWindow::on_actionRefresh_triggered ()
{
        emit onUpdate ();
}

void MainWindow::on_actionSave_as_triggered ()
{
        qDebug () << "MainWindow::on_actionSave_as_triggered() called";
        if (subjectList->length () > 0) {
                QString filename = QFileDialog::getOpenFileName (this, tr ("Speichern unter..."), "C:/Users/Bjoern_Lewe/Desktop/SE/saveData.csv");
                if (!(filename.isNull () || filename.isEmpty ())) {
                        if (saveFile->open (QFile::OpenModeFlag::WriteOnly)) {
                                qDebug () << saveFile->seek (0);
                                QTextStream outstream (saveFile);
                                for (int i = 0; i < subjectList->length (); i++) {
                                        outstream << subjectList->at (i).getSemester () << ";" << subjectList->at (i).getName () << ";";
                                        QList<QString> list;
                                        list.append (subjectList->at (i).getGrade1 ().getGrade () == -1 ? "" : QString::number (subjectList->at (i).getGrade1 ().getGrade ()));
                                        list.append (subjectList->at (i).getGrade2 ().getGrade () == -1 ? "" : QString::number (subjectList->at (i).getGrade2 ().getGrade ()));
                                        list.append (subjectList->at (i).getGrade3 ().getGrade () == -1 ? "" : QString::number (subjectList->at (i).getGrade3 ().getGrade ()));
                                        outstream << createStringList (list) << ";" << subjectList->at (i).getCredits () << "\r\n";
                                }
                                outstream << kolloquium->getName () << ";";
                                QList<QString> kollList;
                                kollList.append (kolloquium->getGrade1 ().getGrade () == -1 ? "" : QString::number (kolloquium->getGrade1 ().getGrade ()));
                                kollList.append (kolloquium->getGrade2 ().getGrade () == -1 ? "" : QString::number (kolloquium->getGrade2 ().getGrade ()));
                                kollList.append (kolloquium->getGrade3 ().getGrade () == -1 ? "" : QString::number (kolloquium->getGrade3 ().getGrade ()));
                                outstream << createStringList (kollList) << ";" << kolloquium->getCredits () << "\r\n";

                                outstream << exam->getName () << ";";
                                QList<QString> examList;
                                examList.append (exam->getGrade1 ().getGrade () == -1 ? "" : QString::number (exam->getGrade1 ().getGrade ()));
                                examList.append (exam->getGrade2 ().getGrade () == -1 ? "" : QString::number (exam->getGrade2 ().getGrade ()));
                                examList.append (exam->getGrade3 ().getGrade () == -1 ? "" : QString::number (exam->getGrade3 ().getGrade ()));
                                outstream << createStringList (examList) << ";" << exam->getCredits () << "\r\n";

                                saveFile->close ();
                        }
                        else{
                                throw QString ("MainWindow::on_actionSave_as_triggered() : Could not open File: " + saveFile->fileName ());
                        }
                }
        }
        else{
                this->close ();
        }
}

void MainWindow::on_actionOpen_File_triggered ()
{
        qDebug () << "MainWindow::on_actionOpen_File_triggered() called";
        QString filename = QFileDialog::getOpenFileName (this, tr ("Datei öffnen"), "C:/Users/Bjoern_Lewe/Desktop/SE/saveData.csv");
        if (!(filename.isNull () || filename.isEmpty ())) {
                this->saveFile = new QFile (filename);
                if (saveFile->open (QFile::OpenModeFlag::ReadOnly)) {
                        QTextStream instream (saveFile);
                        QString data = instream.readAll ();
                        data.replace ("\r\n", "|");
                        data.chop (1);
//                qDebug () << data;
                        QStringList lines = data.split ("|");
//                qDebug () << lines;
                        QList<QStringList> lineSeperated;
                        foreach (auto line, lines) {
                                lineSeperated.append (line.split (";"));
                        }
                        qDebug () << lineSeperated;
                        subjectList->clear ();

                        for (int i = 0; i < lineSeperated.length (); i++) {
                                if (lineSeperated.length () - 2 > i) {
                                        Subject* newSubject = new Subject (lineSeperated.at (i).at (1), lineSeperated.at (i).at (3).toInt ());
                                        newSubject->setSemester (lineSeperated.at (i).at (0).toInt ());
                                        foreach (auto grade, lineSeperated.at (i).at (2).split (",")) {
                                                newSubject->addGrade (Grade (grade.toFloat ()));
                                        }
                                        subjectList->append (*newSubject);
                                }
                                else {
                                        if (lineSeperated.length () - 1 == i) {
                                                FinalExam* newExam = new FinalExam (lineSeperated.at (i).at (0), lineSeperated.at (i).at (2).toInt ());
                                                foreach (auto grade, lineSeperated.at (i).at (1).split (",")) {
                                                        newExam->addGrade (Grade (grade.toFloat ()));
                                                }
//                                                exam = newExam;
                                                exam->setName (newExam->getName ());
                                                exam->setGrade1 (newExam->getGrade1 ());
                                                exam->setGrade2 (newExam->getGrade2 ());
                                                exam->setGrade3 (newExam->getGrade3 ());
                                                exam->setCredits (newExam->getCredits ());
                                        }
                                        else{
                                                Kolloquium* newKoll = new Kolloquium (lineSeperated.at (i).at (0), lineSeperated.at (i).at (2).toInt ());
                                                foreach (auto grade, lineSeperated.at (i).at (1).split (",")) {
                                                        newKoll->addGrade (Grade (grade.toFloat ()));
                                                }
//                                                kolloquium = newKoll;
                                                kolloquium->setName (newKoll->getName ());
                                                kolloquium->setGrade1 (newKoll->getGrade1 ());
                                                kolloquium->setGrade2 (newKoll->getGrade2 ());
                                                kolloquium->setGrade3 (newKoll->getGrade3 ());
                                                kolloquium->setCredits (newKoll->getCredits ());
                                        }
                                }
                        }
                        mapSubjectsToTableView ();
                        saveFile->close ();
                }
        }
}

void MainWindow::mapSubjectsToTableView ()
{
        qDebug () << "MainWindow::mapSubjectsToTableView () called";
        mapper->model ()->removeRows (0, ui->gradeTableOverview->rowCount ());
        for (int i = 0; i < subjectList->length (); i++) {
                ui->gradeTableOverview->insertRow (ui->gradeTableOverview->rowCount ());
                mapper->model ()->setData (mapper->model ()->index (ui->gradeTableOverview->rowCount () - 1, 0), subjectList->at (i).getSemester ());
                mapper->model ()->setData (mapper->model ()->index (ui->gradeTableOverview->rowCount () - 1, 1), subjectList->at (i).getName ());
                QList<QString> list;
                list.append (subjectList->at (i).getGrade1 ().getGrade () == -1 ? "" : QString::number (subjectList->at (i).getGrade1 ().getGrade ()));
                list.append (subjectList->at (i).getGrade2 ().getGrade () == -1 ? "" : QString::number (subjectList->at (i).getGrade2 ().getGrade ()));
                list.append (subjectList->at (i).getGrade3 ().getGrade () == -1 ? "" : QString::number (subjectList->at (i).getGrade3 ().getGrade ()));
                mapper->model ()->setData (mapper->model ()->index (ui->gradeTableOverview->rowCount () - 1, 2), createStringList (list));
                mapper->model ()->setData (mapper->model ()->index (ui->gradeTableOverview->rowCount () - 1, 3), subjectList->at (i).getCredits ());
        }
        emit onUpdate ();
}

void MainWindow::on_actionRemoveSubject_triggered ()
{
        if (!ui->gradeTableOverview->selectedItems ().isEmpty ()) {
                lastRow = ui->gradeTableOverview->selectedItems ().at (0)->row ();
                if (lastRow > -1) {
                        subjectList->removeAt (lastRow);
                        ui->gradeTableOverview->selectRow (lastRow);
                        lastRow = -1;
                        mapSubjectsToTableView ();
                }
        }
}
