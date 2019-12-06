#include "grade.h"

Grade::Grade(float grade)
{
        this->setGrade (grade);
}

float Grade::getGrade () const
{
        return grade;
}

void Grade::setGrade (float value)
{
        grade = value;
}
