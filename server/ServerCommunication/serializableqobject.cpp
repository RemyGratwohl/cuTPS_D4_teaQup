#include "serializableqobject.h"

SerializableQObject::~SerializableQObject(void) {}

void SerializableQObject::insertToDataStream(QDataStream &ds, SerializableType type) const
{
}

void SerializableQObject::extractFromDataStream(QDataStream &ds)
{
}
