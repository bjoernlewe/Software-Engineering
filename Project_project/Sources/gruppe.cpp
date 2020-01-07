#include "Headers/gruppe.h"

Gruppe::Gruppe(int id, int projekt)
{
        this->primaryKey = id;
        this->foreignKey = projekt;
}

int Gruppe::getPrimaryKey () const
{
        return primaryKey;
}

void Gruppe::setPrimaryKey (int value)
{
        primaryKey = value;
}

int Gruppe::getForeignKey () const
{
        return foreignKey;
}

void Gruppe::setForeignKey (int value)
{
        foreignKey = value;
}
