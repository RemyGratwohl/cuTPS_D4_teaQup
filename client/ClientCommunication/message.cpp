#include "message.h"

Message::Message(SerializableQObject *parent) :
    SerializableQObject(parent)
{
}

Message::Message(DEST_TYPE dType, ACTION_TYPE aType)
: destType(dType), actionType(aType)
{}

void Message::insertToDataStream(QDataStream &ds) const
{
}

void Message::extractFromDataStream(QDataStream &ds)
{
}
