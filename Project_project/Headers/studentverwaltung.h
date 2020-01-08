#ifndef STUDENTVERWALTUNG_H
#define STUDENTVERWALTUNG_H

#include <QString>



class StudentVerwaltung
{
public:
StudentVerwaltung(int id, int verwaltung, const QString& username, const QString& password);
QString getUserName () const;
void setUserName (const QString &value);

QString getPassword () const;
void setPassword (const QString &value);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignKey () const;
void setForeignKey (int value);

private:
int primaryKey;
int foreignKey;
QString username;
QString password;
};

#endif // STUDENTVERWALTUNG_H
