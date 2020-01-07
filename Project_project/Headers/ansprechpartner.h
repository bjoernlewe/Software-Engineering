#ifndef ANSPRECHPARTNER_H
#define ANSPRECHPARTNER_H

#include "Headers/person.h"

class Ansprechpartner : public Person
{
public:
Ansprechpartner(int id, const QString& vorname, const QString& nachname, int organisation);

int getForeignKey () const;
void setForeignKey (int value);

private:
int foreignKey;
};

#endif // ANSPRECHPARTNER_H
