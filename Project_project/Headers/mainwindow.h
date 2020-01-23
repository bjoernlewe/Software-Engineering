#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDataWidgetMapper>
#include <QMainWindow>
#include "insertprojectdialog.h"
#include "databaseinterface.h"
#include "organisationscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;
               class InsertProjectDialog;
               class LoginScreen; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr, DatabaseInterface* db = nullptr);
~MainWindow();

void login ();

QString getRole () const;
void setRole (const QString &value);

QString getType () const;
void setType (const QString &value);

int getCurrentlyLoggedIn () const;
void setCurrentlyLoggedIn (int value);

signals:
void onUpdate ();
void backToLogin ();
void changeMapperIndex (int index);

private:
Ui::MainWindow *ui;
QString type;
int lastClickedRow = -1;
QDataWidgetMapper* mapper;
int currentlyLoggedIn = -1;
QList<QWidget*> widgets;
QListView* view;
void setAppropriateWidgetsHidden (const QModelIndex* index = nullptr);
void setAppropriateWidgetsEnabled (const QString* type = nullptr);
void initializeWidgetList ();
void setWidgetVisible (QWidget* widget);
void setupMapper ();

protected:
DatabaseInterface* dbInterface;

private slots:
void MapperIndexChanged (int index);
void on_actionLog_Out_triggered ();
void on_actionGruppe_triggered ();
void on_actionOrganisation_triggered ();
void on_login ();
void on_ProjektList_activated (const QModelIndex &index);
void on_ProjektList_entered (const QModelIndex &index);
void on_ProjektList_clicked (const QModelIndex &index);
void on_ProjektTree_clicked (const QModelIndex &index);
void on_ProjektTree_activated (const QModelIndex &index);
void on_ProjektTree_entered (const QModelIndex &index);
void on_statusCombo_currentIndexChanged (int index);
void on_orgCombo_currentIndexChanged (int index);
void on_ansprechCombo_currentIndexChanged (int index);
void on_dozentCombo_currentIndexChanged (int index);
void on_comboBox_3_currentIndexChanged (int index);
void on_comboBox_2_currentIndexChanged (int index);
void on_comboBox_1_currentIndexChanged (int index);
void on_textEdit_2_textChanged ();
void on_textEdit_1_textChanged ();
void on_lineEdit_1_editingFinished ();
};
#endif // MAINWINDOW_H
