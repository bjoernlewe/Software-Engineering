#include "Headers/verwaltung.h"

Verwaltung::Verwaltung(int id, int student, int ansprechpartner)
{
        primaryKey = id;
        foreignStuKey = student;
        foreignAnsKey = ansprechpartner;
}

int Verwaltung::getPrimaryKey () const
{
        return primaryKey;
}

void Verwaltung::setPrimaryKey (int value)
{
        primaryKey = value;
}

int Verwaltung::getForeignStuKey () const
{
        return foreignStuKey;
}

void Verwaltung::setForeignStuKey (int value)
{
        foreignStuKey = value;
}

int Verwaltung::getForeignAnsKey () const
{
        return foreignAnsKey;
}

void Verwaltung::setForeignAnsKey (int value)
{
        foreignAnsKey = value;
}
