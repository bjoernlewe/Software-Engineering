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
        grade1 = new Grade ();
        grade2 = new Grade ();
        grade3 = new Grade ();
}

GradedItem::~GradedItem()
{
        qDebug () << "GradedItem::~GradedItem() called";
}

const QString GradedItem::getType ()
{
        qDebug () << "GradedItem::getType() called";
        return "GradedItem";
}


bool GradedItem::addGrade (Grade grade)
{
        qDebug () << "GradedItem::addGrade() called";
        if (grade1->getGrade () <= 0) {
                setGrade1 (grade.getGrade ());
                return true;
        }
        else if (grade2->getGrade () <= 0) {
                setGrade2 (grade.getGrade ());
                return true;
        }
        else if (grade3->getGrade () <= 0) {
                setGrade3 (grade.getGrade ());
                return true;
        }
        else{
                throw  QString ("GradedItem::addGrade() : Too many Grades added to Object.");
        }
}


bool GradedItem::removeGrade (int index)
{
        qDebug () << "GradedItem::removeGrade() called";
        switch (index) {
        case 1:
                if (grade1 != nullptr) {
                        delete grade1;
                        return true;
                }
                break;

        case 2:
                if (grade2 != nullptr) {
                        delete grade2;
                        return true;
                }
                break;

        case 3:
                if (grade3 != nullptr) {
                        delete grade3;
                        return true;
                }
                break;

        default:
                return false;
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

QString GradedItem::getGradeListTxt () const
{
        QString gradeList;

        if (grade1->getGrade () >= 0) {
                gradeList.append (QString::number (grade1->getGrade ()));
                if (grade2->getGrade () >= 0)
                        gradeList.append (", ");
        }
        if (grade2->getGrade () >= 0) {
                gradeList.append (QString::number (grade2->getGrade ()));
                if (grade3->getGrade () >= 0)
                        gradeList.append (", ");
        }
        if (grade3->getGrade () >= 0) {
                gradeList.append (QString::number (grade3->getGrade ()));
        }
        return (gradeList.isEmpty () || gradeList.isNull ()) ? "" : gradeList;
}

float GradedItem::getLastGrade () const
{
        if (grade1->getGrade () == 5.0f) {
                if (grade2->getGrade () == 5.0f) {
                        return grade3->getGrade ();
                }
        }
}

Grade GradedItem::getGrade1 () const
{
        return *grade1;
}

void GradedItem::setGrade1 (Grade value)
{
        *grade1 = value;
}

Grade GradedItem::getGrade2 () const
{
        return *grade2;
}

void GradedItem::setGrade2 (Grade value)
{
        *grade2 = value;
}

Grade GradedItem::getGrade3 () const
{
        return *grade3;
}

void GradedItem::setGrade3 (Grade value)
{
        *grade3 = value;
}
