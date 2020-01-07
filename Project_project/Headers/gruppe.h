#ifndef GRUPPE_H
#define GRUPPE_H


class Gruppe
{
public:
Gruppe(int id, int projekt);

int getPrimaryKey () const;
void setPrimaryKey (int value);

int getForeignKey () const;
void setForeignKey (int value);

private:
int primaryKey;
int foreignKey;
};

#endif // GRUPPE_H
