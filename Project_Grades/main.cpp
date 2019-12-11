#include "mainwindow.h"
#include <QApplication>

int main (int argc, char *argv[])
{
        try {
                QApplication a (argc, argv);
                MainWindow w;
                w.show ();


                return a.exec ();
        } catch (QString exception) {
                qDebug () << "Exception caught in Main : " << exception;
                return -1;
        }
        return 0;
}
