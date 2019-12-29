#include "Headers/mainwindow.h"

#include <QApplication>
#include <QDebug>

int main (int argc, char *argv[])
{
        try {
                QApplication a (argc, argv);
                qDebug () << "App path : " << qApp->applicationDirPath ();
                MainWindow w;
                w.show ();
                return a.exec ();
        } catch (QString exception) {
                qDebug () << exception;
        }
        return 0;
}
