#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "insertprojectdialog.h"
#include "databaseinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
               class InsertProjectDialog; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();

QString getRole () const;
void setRole (const QString &value);

private slots:
void on_actionStudent_triggered ();

void on_actionDozent_triggered ();

void on_insertProject_clicked ();

void refresh ();

public slots:
void newInsert (int projID, const QString& projName, const QString& projBesc, const QString& projHinter, const QString& projAnspr, const QString& projStudent);

signals:
void onUpdate ();

private:
Ui::MainWindow *ui;

protected:
DatabaseInterface dbInterface;
QString role;
};
#endif // MAINWINDOW_H
