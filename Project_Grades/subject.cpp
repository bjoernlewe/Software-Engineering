#include "subject.h"

Subject::Subject(QString name, int credits) : GradedItem (name, credits)
{
}

const QString Subject::getType ()
{
        return "Subject";
}

int Subject::getSemester () const
{
        return semester;
}

void Subject::setSemester (int value)
{
        semester = value;
}
