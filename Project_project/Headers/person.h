#ifndef PERSON_H
#define PERSON_H

#include <QString>



class Person
{
public:
Person(int id, const QString& vorname, const QString& nachname);


int getPrimaryKey () const;
void setPrimaryKey (int value);

QString getVorname () const;
void setVorname (const QString &value);

QString getNachname () const;
void setNachname (const QString &value);

private:
int primaryKey;
QString vorname;
QString nachname;
};

#endif // PERSON_H
