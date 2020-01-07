#include "Headers/person.h"

Person::Person(int id, const QString& vorname, const QString& nachname)
{
        this->primaryKey = id;
        this->vorname = vorname;
        this->nachname = nachname;
}

int Person::getPrimaryKey () const
{
        return primaryKey;
}

void Person::setPrimaryKey (int value)
{
        primaryKey = value;
}

QString Person::getVorname () const
{
        return vorname;
}

void Person::setVorname (const QString &value)
{
        vorname = value;
}

QString Person::getNachname () const
{
        return nachname;
}

void Person::setNachname (const QString &value)
{
        nachname = value;
}
