#ifndef VERWALTUNG_H
#define VERWALTUNG_H


class Verwaltung
{
public:
Verwaltung(int id, int student, int ansprechpartner);
int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignStuKey () const;
void setForeignStuKey (int value);

int getForeignAnsKey () const;
void setForeignAnsKey (int value);

private:
int primaryKey;
int foreignStuKey;
int foreignAnsKey;
};

#endif // VERWALTUNG_H
