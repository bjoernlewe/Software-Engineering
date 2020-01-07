#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "insertprojectdialog.h"
#include "databaseinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
               class InsertProjectDialog;
               class LoginScreen; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();

QString getRole () const;
void setRole (const QString &value);

signals:
void onUpdate ();
void backToLogin ();

private:
Ui::MainWindow *ui;

protected:
DatabaseInterface dbInterface;
private slots:
void on_actionLog_Out_triggered ();
void on_actionGruppe_triggered ();
};
#endif // MAINWINDOW_H
