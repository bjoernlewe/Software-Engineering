#include "Headers/mainwindow.h"
#include "Headers/loginscreen.h"

#include <QApplication>
#include <QDebug>

int main (int argc, char *argv[])
{
        try {
                QApplication a (argc, argv);
                qDebug () << "App path : " << qApp->applicationDirPath ();
                MainWindow* m = new MainWindow ();
                LoginScreen l (m);
                l.show ();
                return a.exec ();
        } catch (QString exception) {
                qDebug () << exception;
        }
        return 0;
}
