#ifndef SUBJECT_H
#define SUBJECT_H

#include "gradeditem.h"

class Subject : public GradedItem
{
public:
Subject(QString name, int credits);
const QString getType () override;
};

#endif // SUBJECT_H
