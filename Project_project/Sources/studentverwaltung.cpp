#include "Headers/studentverwaltung.h"

StudentVerwaltung::StudentVerwaltung(int id, int verwaltung, const QString& vorname, const QString& nachname, const QString& password)
{
        primaryKey = id;
        foreignKey = verwaltung;
        this->vorname = vorname;
        this->nachname = nachname;
        this->password = password;
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

QString StudentVerwaltung::getVorname () const
{
        return vorname;
}

void StudentVerwaltung::setVorname (const QString &value)
{
        vorname = value;
}

QString StudentVerwaltung::getNachname () const
{
        return nachname;
}

void StudentVerwaltung::setNachname (const QString &value)
{
        nachname = value;
}
