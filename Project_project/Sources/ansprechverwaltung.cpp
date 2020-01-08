#include "Headers/ansprechverwaltung.h"

AnsprechVerwaltung::AnsprechVerwaltung(int id, int verwaltung, const QString& username, const QString& password)
{
        primaryKey = id;
        foreignKey = verwaltung;
        this->username = username;
        this->password = password;
}

int AnsprechVerwaltung::getPrimaryKey () const
{
        return primaryKey;
}

void AnsprechVerwaltung::setPrimaryKey (int value)
{
        primaryKey = value;
}

int AnsprechVerwaltung::getForeignKey () const
{
        return foreignKey;
}

void AnsprechVerwaltung::setForeignKey (int value)
{
        foreignKey = value;
}

QString AnsprechVerwaltung::getUserName () const
{
        return username;
}

void AnsprechVerwaltung::setUserName (const QString &value)
{
        username = value;
}

QString AnsprechVerwaltung::getPassword () const
{
        return password;
}

void AnsprechVerwaltung::setPassword (const QString &value)
{
        password = value;
}
