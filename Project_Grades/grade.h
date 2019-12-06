#ifndef GRADE_H
#define GRADE_H


class Grade
{
public:
Grade(float grade);

float getGrade () const;
void setGrade (float value);

private:
float grade;
};

#endif // GRADE_H
