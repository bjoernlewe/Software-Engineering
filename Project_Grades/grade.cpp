#include "grade.h"

Grade::Grade(float grade)
{
        constraint = new QList<float>();
        constraint->append (0);
        constraint->append (-1);
        constraint->append (1.0f);
        constraint->append (1.3f);
        constraint->append (1.7f);
        constraint->append (2.0f);
        constraint->append (2.3f);
        constraint->append (2.7f);
        constraint->append (3.0f);
        constraint->append (3.3f);
        constraint->append (3.7f);
        constraint->append (4.0f);
        constraint->append (5.0f);
        this->setGrade (grade);
}

Grade::~Grade()
{
}

float Grade::getGrade () const
{
        return grade;
}

void Grade::setGrade (float value)
{
        if (constraintCheck (value)) {
                grade = value;
        }
        else{
                throw QString ("Grade::setGrade() :" + QString::number (value) + " not specified in Constraint");
        }
}

bool Grade::constraintCheck (float grade)
{
        for (int i = 0; i < constraint->length (); i++) {
                if (grade == constraint->at (i)) {
                        return true;
                }
        }
        return false;
}
