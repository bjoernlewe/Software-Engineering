#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>
#include <QCloseEvent>
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


private slots:
void on_buttonToExamsDialog_clicked ();

void on_actionAddNewSubject_triggered ();

void on_actionExit_triggered ();
void closeEvent (QCloseEvent *e) override;

void saveDialog (QWidget* widget);

void exitWindowSlot (QDialog* window);

void on_gradeTableOverview_itemDoubleClicked (QTableWidgetItem *item);

signals:
void onUpdate ();

private:
Ui::MainWindow *ui;
float average = 0.0;
QList<Subject> subjectList, subjectBufferList;
FinalExam* exam, *examBuffer;
Kolloquium* kolloquium, *kolloquiumBuffer;
};

#endif // MAINWINDOW_H
