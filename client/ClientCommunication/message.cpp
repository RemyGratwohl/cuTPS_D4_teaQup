#include "message.h"

Message::Message(void) :
    destType(static_cast<DEST_TYPE>(0)),
    actionType(static_cast<ACTION_TYPE>(0)),
    user(0),
    userIsShared(true)
{}

Message::Message(DEST_TYPE dType, ACTION_TYPE aType, User* u) :
    destType(dType),
    actionType(aType),
    user(u),
    userIsShared(true)
{}

Message::~Message(void) {
    if( !userIsShared && user != 0 ) {
        delete user;
        user = 0;
    }
}

void Message::insertToDataStream(QDataStream& ds, SerializableType type) const {
    SerializableQObject::insertToDataStream(ds, type);
    user->insertToDataStream(ds);
}

void Message::extractFromDataStream(QDataStream& ds) {
    SerializableQObject::extractFromDataStream(ds);
    userIsShared = false;
    user = new User();
    user->extractFromDataStream(ds);
}

User* Message::extractUser(void) {
    User* temp = user;
    user = 0;
    userIsShared = true;
    return temp;
}
