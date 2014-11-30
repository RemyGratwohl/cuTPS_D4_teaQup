#include "message.h"

Message::Message(DEST_TYPE dType, ACTION_TYPE aType, User* u)
    : destType(dType), actionType(aType), user(u)
{}

void Message::insertToDataStream(QDataStream& ds) const {

}

void Message::extractFromDataStream(QDataStream& ds) {

}
