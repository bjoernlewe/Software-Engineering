#ifndef ORGANISATION_H
#define ORGANISATION_H

#include <QString>



class Organisation
{
public:
Organisation(int id, int projekt, int ansprechpartner, const QString& name);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignProKey () const;
void setForeignProKey (int value);

int getForeignAnsKey () const;
void setForeignAnsKey (int value);

QString getOrganisationName () const;
void setOrganisationName (const QString &value);

private:
int primaryKey;
int foreignProKey;
int foreignAnsKey;
QString organisationName;
};

#endif // ORGANISATION_H
