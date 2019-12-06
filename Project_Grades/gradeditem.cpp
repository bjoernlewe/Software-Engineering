#include "gradeditem.h"

GradedItem::GradedItem(QString name, int credits)
{
        qDebug () << "GradedItem::GradedItem() called";
        if (name.isNull () || name.isEmpty ()) {
                throw QString ("GradedItem::GradedItem() : no Name was given");
        }
        if (credits < 0) {
                throw QString ("GradedItem::GradedItem() : credits are negative");
        }
        this->name = name;
        this->credits = credits;
}

GradedItem::~GradedItem()
{
        qDebug () << "GradedItem::~GradedItem() called";
        gradeList.clear ();
}

const QString GradedItem::getType ()
{
        qDebug () << "GradedItem::getType() called";
        return "GradedItem";
}


bool GradedItem::addGrade (Grade grade)
{
        qDebug () << "GradedItem::addGrade() called";
        if (grade.getGrade () < 0) {
                throw QString ("GradedItem::addGrade() : Grade object with negative grade constant was given");
        }
        gradeList.append (grade);
        return true;
}

bool GradedItem::removeGrade (Grade grade)
{
        qDebug () << "GradedItem::removeGrade() called";
        for (int i = 0; i < gradeList.length (); i++) {
                if (gradeList.at (i).getGrade () >= grade.getGrade ()
                    && gradeList.at (i).getGrade () <= grade.getGrade ()) {
                        gradeList.removeAt (i);
                        return true;
                }
        }
        return false;
}

QString GradedItem::getName () const
{
        return name;
}

void GradedItem::setName (const QString &value)
{
        name = value;
}

int GradedItem::getCredits () const
{
        return credits;
}

void GradedItem::setCredits (int value)
{
        credits = value;
}

QString GradedItem::getGradeListTxt ()
{
        QString gradeListTxt;

        for (int i = 0; i < this->gradeList.length (); i++) {
                qDebug () << gradeListTxt;
                gradeListTxt.append (QString::number (gradeList.at (i).getGrade ()));
        }
        return gradeListTxt;
}

QList<Grade> GradedItem::getGradeList () const
{
        return gradeList;
}

void GradedItem::setGradeList (const QList<Grade> &value)
{
        gradeList = value;
}
