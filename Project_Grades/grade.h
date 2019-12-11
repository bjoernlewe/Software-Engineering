#ifndef GRADE_H
#define GRADE_H

#include <QList>

class Grade
{
public:
Grade(float grade = -1);
~Grade();

float getGrade () const;
void setGrade (float value);

private:
float grade;
bool constraintCheck (float grade);
QList<float>* constraint;
};

#endif // GRADE_H
