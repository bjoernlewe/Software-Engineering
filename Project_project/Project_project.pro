QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/addansdialog.cpp \
    Sources/addorgdialog.cpp \
    Sources/ansprechpartner.cpp \
    Sources/ansprechverwaltung.cpp \
    Sources/databaseinterface.cpp \
    Sources/gruppe.cpp \
    Sources/insertprojectdialog.cpp \
    Sources/loginscreen.cpp \
    Sources/main.cpp \
    Sources/mainwindow.cpp \
    Sources/organisation.cpp \
    Sources/organisationscreen.cpp \
    Sources/person.cpp \
    Sources/projekt.cpp \
    Sources/singinscreen.cpp \
    Sources/student.cpp \
    Sources/studentverwaltung.cpp \
    Sources/verwaltung.cpp

HEADERS += \
    Forms/addansdialog.h \
    Forms/addorgdialog.h \
    Forms/organisationscreen.h \
    Headers/addansdialog.h \
    Headers/addorgdialog.h \
    Headers/ansprechpartner.h \
    Headers/ansprechverwaltung.h \
    Headers/databaseinterface.h \
    Headers/gruppe.h \
    Headers/insertprojectdialog.h \
    Headers/loginscreen.h \
    Headers/mainwindow.h \
    Headers/organisation.h \
    Headers/organisationscreen.h \
    Headers/person.h \
    Headers/projekt.h \
    Headers/singinscreen.h \
    Headers/student.h \
    Headers/studentverwaltung.h \
    Headers/verwaltung.h

FORMS += \
    Forms/addansdialog.ui \
    Forms/addorgdialog.ui \
    Forms/insertprojectdialog.ui \
    Forms/loginscreen.ui \
    Forms/mainwindow.ui \
    Forms/organisationscreen.ui \
    Forms/singinscreen.ui \
    Forms/vertikalerTestDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Sql/projektverwaltung.sql \ \
    Sql/testCaseSelectStatement.sql
