#include "Headers/projekt.h"


Projekt::Projekt(int id, int organisation, int gruppe, const QString &name, const QString &beschreibung, const QString &hintergrund, bool status)
{
        this->primaryKey = id;
        this->foreignOrgKey = organisation;
        this->foreignGruKey = gruppe;
        this->projektName = name;
        this->beschreibung = beschreibung;
        this->hintergrund = hintergrund;
        this->status = status;
}

int Projekt::getPrimaryKey () const
{
        return primaryKey;
}

void Projekt::setPrimaryKey (int value)
{
        primaryKey = value;
}

int Projekt::getForeignOrgKey () const
{
        return foreignOrgKey;
}

void Projekt::setForeignOrgKey (int value)
{
        foreignOrgKey = value;
}

int Projekt::getForeignGruKey () const
{
        return foreignGruKey;
}

void Projekt::setForeignGruKey (int value)
{
        foreignGruKey = value;
}

QString Projekt::getProjektName () const
{
        return projektName;
}

void Projekt::setProjektName (const QString &value)
{
        projektName = value;
}

QString Projekt::getBeschreibung () const
{
        return beschreibung;
}

void Projekt::setBeschreibung (const QString &value)
{
        beschreibung = value;
}

QString Projekt::getHintergrund () const
{
        return hintergrund;
}

void Projekt::setHintergrund (const QString &value)
{
        hintergrund = value;
}

bool Projekt::getStatus () const
{
        return status;
}

void Projekt::setStatus (bool value)
{
        status = value;
}
