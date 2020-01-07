#include "Headers/organisation.h"

Organisation::Organisation(int id, int projekt, int ansprechpartner, const QString& name)
{
        this->primaryKey = id;
        this->foreignProKey = projekt;
        this->foreignAnsKey = ansprechpartner;
        this->organisationName = name;
}

int Organisation::getPrimaryKey () const
{
        return primaryKey;
}

void Organisation::setPrimaryKey (int value)
{
        primaryKey = value;
}

int Organisation::getForeignProKey () const
{
        return foreignProKey;
}

void Organisation::setForeignProKey (int value)
{
        foreignProKey = value;
}

int Organisation::getForeignAnsKey () const
{
        return foreignAnsKey;
}

void Organisation::setForeignAnsKey (int value)
{
        foreignAnsKey = value;
}

QString Organisation::getOrganisationName () const
{
        return organisationName;
}

void Organisation::setOrganisationName (const QString &value)
{
        organisationName = value;
}
