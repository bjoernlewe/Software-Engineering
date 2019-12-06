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
bool removeGrade (Grade grade);
QString getName () const;
void setName (const QString &value);
int getCredits () const;
void setCredits (int value);
QString getGradeListTxt ();

QList<Grade> getGradeList () const;
void setGradeList (const QList<Grade> &value);

private:
QList<Grade> gradeList;
QString name;
int credits;
};

#endif // GRADEDITEM_H
