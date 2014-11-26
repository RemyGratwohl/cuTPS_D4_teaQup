#include "message.h"

Message::Message(SerializableQObject *parent) :
    SerializableQObject(parent)
{
}

Message::Message(DEST_TYPE dType, ACTION_TYPE aType, QVector<SerializableQObject *> vType)
: destType(dType), actionType(aType), data(vType)
{}

void Message::insertToDataStream(QDataStream &ds) const
{
}

void Message::extractFromDataStream(QDataStream &ds)
{
}
