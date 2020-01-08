#ifndef ANSPRECHVERWALTUNG_H
#define ANSPRECHVERWALTUNG_H

#include <QString>



class AnsprechVerwaltung
{
public:
AnsprechVerwaltung(int id, int verwaltung, const QString& username, const QString& password);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignKey () const;
void setForeignKey (int value);

QString getUserName () const;
void setUserName (const QString &value);

QString getPassword () const;
void setPassword (const QString &value);

private:
int primaryKey;
int foreignKey;
QString username;
QString password;
};

#endif // ANSPRECHVERWALTUNG_H
