#include "finalexam.h"

FinalExam::FinalExam(QString name, int credits) : GradedItem (name, credits)
{
}

const QString FinalExam::getType ()
{
        return "FinalExam";
}
