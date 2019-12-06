#include "subject.h"

Subject::Subject(QString name, int credits) : GradedItem (name, credits)
{
}

const QString Subject::getType ()
{
        return "Subject";
}
