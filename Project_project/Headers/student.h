#ifndef STUDENT_H
#define STUDENT_H

#include "Headers/person.h"

class Student : public Person
{
public:
Student(int id, const QString& vorname, const QString& nachname, int gruppe);

int getForeignKey () const;
void setForeignKey (int value);

private:
int foreignKey;
};

#endif // STUDENT_H
