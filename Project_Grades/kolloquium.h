#ifndef KOLLOQUIUM_H
#define KOLLOQUIUM_H

#include "gradeditem.h"

class Kolloquium : public GradedItem
{
public:
Kolloquium(QString name, int credits);
const QString getType () override;
};

#endif // KOLLOQUIUM_H
