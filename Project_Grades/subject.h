#ifndef SUBJECT_H
#define SUBJECT_H

#include "gradeditem.h"

class Subject : public GradedItem
{
public:
Subject(QString name, int credits);
const QString getType () override;

int getSemester () const;
void setSemester (int value);

private:
int semester;
};

#endif // SUBJECT_H
