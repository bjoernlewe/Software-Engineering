#ifndef PROJEKT_H
#define PROJEKT_H

#include <QString>



class Projekt
{
public:
Projekt(int id, int organisation, int gruppe, int dozent, const QString& name, const QString& beschreibung, const QString& hintergrund, bool status);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignOrgKey () const;
void setForeignOrgKey (int value);

int getForeignGruKey () const;
void setForeignGruKey (int value);

QString getProjektName () const;
void setProjektName (const QString &value);

QString getBeschreibung () const;
void setBeschreibung (const QString &value);

QString getHintergrund () const;
void setHintergrund (const QString &value);

int getStatus () const;
void setStatus (int value);

int getForeignDozKey () const;
void setForeignDozKey (int value);

private:
int primaryKey;
int foreignOrgKey;
int foreignGruKey;
int foreignDozKey;
QString projektName;
QString beschreibung;
QString hintergrund;
int status;
};

#endif // PROJEKT_H
