#include "Headers/ansprechpartner.h"

Ansprechpartner::Ansprechpartner(int id, const QString& vorname, const QString& nachname, int organisation) : Person (id, vorname, nachname)
{
        this->foreignKey = organisation;
}

int Ansprechpartner::getForeignKey () const
{
        return foreignKey;
}

void Ansprechpartner::setForeignKey (int value)
{
        foreignKey = value;
}
