#include "datamessage.h"

DataMessage::DataMessage(DEST_TYPE dt, ACTION_TYPE at, User* u, QVector<SerializableQObject *> data_) :
    Message(dt, at, u), data(data_)
{
}

void DataMessage::insertToDataStream(QDataStream& ds) const {

}

void DataMessage::extractFromDataStream(QDataStream& ds) {

}
