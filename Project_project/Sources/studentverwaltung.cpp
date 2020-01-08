#include "Headers/studentverwaltung.h"

StudentVerwaltung::StudentVerwaltung(int id, int verwaltung, const QString& username, const QString& password)
{
        primaryKey = id;
        foreignKey = verwaltung;
        this->username = username;
        this->password = password;
}

QString StudentVerwaltung::getUserName () const
{
        return username;
}

void StudentVerwaltung::setUserName (const QString &value)
{
        username = value;
}

QString StudentVerwaltung::getPassword () const
{
        return password;
}

void StudentVerwaltung::setPassword (const QString &value)
{
        password = value;
}

int StudentVerwaltung::getPrimaryKey () const
{
        return primaryKey;
}

void StudentVerwaltung::setPrimaryKey (int value)
{
        primaryKey = value;
}

int StudentVerwaltung::getForeignKey () const
{
        return foreignKey;
}

void StudentVerwaltung::setForeignKey (int value)
{
        foreignKey = value;
}
