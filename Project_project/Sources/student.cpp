#include "Headers/student.h"

Student::Student(int id, const QString& vorname, const QString& nachname, int gruppe) : Person (id, vorname, nachname)
{
        this->foreignKey = gruppe;
}

int Student::getForeignKey () const
{
        return foreignKey;
}

void Student::setForeignKey (int value)
{
        foreignKey = value;
}
