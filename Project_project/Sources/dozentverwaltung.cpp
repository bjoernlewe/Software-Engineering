#include "Headers/dozentverwaltung.h"

DozentVerwaltung::DozentVerwaltung(int id, int verwaltung, const QString& vorname, const QString& nachname, const QString& password)
{
        primaryKey = id;
        foreignKey = verwaltung;
        this->vorname = vorname;
        this->nachname = nachname;
        this->password = password;
}

int DozentVerwaltung::getPrimaryKey () const
{
        return primaryKey;
}

void DozentVerwaltung::setPrimaryKey (int value)
{
        primaryKey = value;
}

int DozentVerwaltung::getForeignKey () const
{
        return foreignKey;
}

void DozentVerwaltung::setForeignKey (int value)
{
        foreignKey = value;
}

QString DozentVerwaltung::getPassword () const
{
        return password;
}

void DozentVerwaltung::setPassword (const QString &value)
{
        password = value;
}

QString DozentVerwaltung::getVorname () const
{
        return vorname;
}

void DozentVerwaltung::setVorname (const QString &value)
{
        vorname = value;
}

QString DozentVerwaltung::getNachname () const
{
        return nachname;
}

void DozentVerwaltung::setNachname (const QString &value)
{
        nachname = value;
}
