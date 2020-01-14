#ifndef STUDENTVERWALTUNG_H
#define STUDENTVERWALTUNG_H

#include <QString>



class StudentVerwaltung
{
public:
StudentVerwaltung(int id, int verwaltung, const QString& vorname, const QString& nachname, const QString& password);

QString getPassword () const;
void setPassword (const QString &value);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignKey () const;
void setForeignKey (int value);

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

#endif // STUDENTVERWALTUNG_H
