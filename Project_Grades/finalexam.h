#ifndef FINALEXAM_H
#define FINALEXAM_H

#include "gradeditem.h"

class FinalExam : public GradedItem
{
public:
FinalExam(QString name, int credits);
const QString getType () override;
};

#endif // FINALEXAM_H
