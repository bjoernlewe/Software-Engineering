#include "kolloquium.h"

Kolloquium::Kolloquium(QString name, int credits) : GradedItem (name, credits)
{
}

const QString Kolloquium::getType ()
{
        return "Kolloquium";
}
