#include "course.h"

Course::Course() :
    identifier(0),
    name(),
    termID(0)
{}

Course::Course(const OBJ_ID_TYPE id,
               const QString& n, const OBJ_ID_TYPE tID) :
    identifier(id),
    name(n),
    termID(tID)
{}

void Course::insertToDataStream(QDataStream& ds) const {
        SerializableQObject::insertToDataStream(ds, COURSEOBJ);
}
