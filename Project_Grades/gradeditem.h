#ifndef GRADEDITEM_H
#define GRADEDITEM_H

#include "grade.h"
#include <QString>
#include <QList>
#include <QDebug>

class GradedItem
{
public:
GradedItem(QString name, int credits = 0);
virtual ~GradedItem();
virtual const QString getType ();
bool addGrade (Grade grade);
bool removeGrade (int index);
QString getName () const;
void setName (const QString &value);
int getCredits () const;
void setCredits (int value);
QString getGradeListTxt () const;
virtual float getLastGrade () const;


Grade getGrade1 () const;
void setGrade1 (Grade value);

Grade getGrade2 () const;
void setGrade2 (Grade value);

Grade getGrade3 () const;
void setGrade3 (Grade value);

private:
Grade* grade1;
Grade* grade2;
Grade* grade3;
QString name;
int credits;
};

#endif // GRADEDITEM_H
