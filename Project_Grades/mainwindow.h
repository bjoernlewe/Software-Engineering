#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QDialog>
#include <QLineEdit>
#include <QGraphicsColorizeEffect>
#include <QColor>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QDataWidgetMapper>
#include <QAbstractTableModel>
#include <QFileDialog>
#include "subject.h"
#include "finalexam.h"
#include "kolloquium.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
explicit MainWindow(QWidget *parent = nullptr);
~MainWindow() override;
void calculateAverage ();
void mapSubjectsToTableView ();
QString createStringList (QList<QString> list);


private slots:
void on_buttonToExamsDialog_clicked ();

void on_actionAddNewSubject_triggered ();

void on_actionExit_triggered ();

void closeEvent (QCloseEvent *e) override;

void saveDialog (QWidget* widget);

void exitWindowSlot (QDialog* window);

void on_gradeTableOverview_itemDoubleClicked (QTableWidgetItem *item);

void on_actionRefresh_triggered ();

void on_actionSave_as_triggered ();

void on_actionOpen_File_triggered ();



void on_actionRemoveSubject_triggered ();

signals:
void onUpdate ();

private:
void replaceOrInsert (int index, const QString &data);
bool checkConstraint (float value);
QString defaultFilePath;
QLineEdit* changeToWarningColor (QLineEdit* edit);
QList<float>* constraint;
Ui::MainWindow *ui;
QDataWidgetMapper* mapper;
QList<QString>* valueListBuffer;
QStringList* columnLabels;
float average = 0.0;
int lastRow;
QList<Subject>* subjectList, *subjectBufferList;
FinalExam* exam, *examBuffer;
Kolloquium* kolloquium, *kolloquiumBuffer;
QFile* saveFile;
};

#endif // MAINWINDOW_H
