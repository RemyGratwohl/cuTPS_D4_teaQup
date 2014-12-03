#include "term.h"
#include <QtDebug>

Term::Term() :
    identifier(0),
    semester(static_cast<SEMESTER>(0)),
    year(0)
{}

Term::Term(const OBJ_ID_TYPE id,
           const QString& s, const quint16 year) :
    identifier(id),
    semester(static_cast<SEMESTER>(0)),
    year(year)
{
    setSemester(s);
}

void Term::insertToDataStream(QDataStream& ds) const {
        SerializableQObject::insertToDataStream(ds, TERMOBJ);
}

QString Term::getSemester(void) const {
    switch(semester) {
    case FALL:
        return "Fall";
    case WINTER:
        return "Winter";
    case SUMMER:
        return "Summer";
    default:
        qDebug() << "Term::getSemester : object has unknown semester: "
                 << static_cast<quint16>(semester) << ".";
        return "Unknown";
    }
}

bool Term::setSemester(const QString& s) {
    QString sLower = s.toLower();
    if( sLower == "fall" || sLower == "f" ) {
        semester = FALL;
    } else if( sLower == "winter" || sLower == "w" ) {
        semester = WINTER;
    } else if( sLower == "summer" || sLower == "s" ) {
        semester = SUMMER;
    } else {
        qDebug() << "Term::setSemester : Unknown semester: "
                 << s << ".";
        return false;
    }
    return true;
}
