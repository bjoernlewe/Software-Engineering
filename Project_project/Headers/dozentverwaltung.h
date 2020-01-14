#ifndef ANSPRECHVERWALTUNG_H
#define ANSPRECHVERWALTUNG_H

#include <QString>



class DozentVerwaltung
{
public:
DozentVerwaltung(int id, int verwaltung, const QString& vorname, const QString& nachname, const QString& password);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignKey () const;
void setForeignKey (int value);

QString getPassword () const;
void setPassword (const QString &value);

QString getVorname () const;
void setVorname (const QString &value);

QString getNachname () const;
void setNachname (const QString &value);

private:
int primaryKey;
int foreignKey;
QString vorname;
QString nachname;
QString password;
};

#endif // ANSPRECHVERWALTUNG_H
