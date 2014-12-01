#include "course.h"

Course::Course() :
    identifier(0),
    name(),
    termID(0)
{}

Course::Course(const quint16 id,
               const QString& n, const quint16 tID) :
    identifier(id),
    name(n),
    termID(tID)
{}

void Course::insertToDataStream(QDataStream& ds) const {
        SerializableQObject::insertToDataStream(ds, COURSEOBJ);
}
