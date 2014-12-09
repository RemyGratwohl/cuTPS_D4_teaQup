#include "message.h"

Message::Message(void) :
    destType(INVALIDDEST),
    actionType(INVALIDACTION),
    user(0),
    userIsShared(true),
    userExists(false)
{}

Message::Message(DEST_TYPE dType, ACTION_TYPE aType, User* u) :
    destType(dType),
    actionType(aType),
    user(u),
    userIsShared(true)
{
    userExists = (user != 0);
}

Message::~Message(void) {
    if( !userIsShared && user != 0 ) {
        delete user;
        user = 0;
    }
}

void Message::insertToDataStream(QDataStream& ds, SerializableType type) const {
    SerializableQObject::insertToDataStream(ds, type);
    if( userExists ) {
        user->insertToDataStream(ds);
    }
}

void Message::extractFromDataStream(QDataStream& ds) {
    SerializableQObject::extractFromDataStream(ds);
    userIsShared = false;
    if( userExists ) {
        user = new User();
        user->extractFromDataStream(ds);
    }
}

User* Message::extractUser(void) {
    if( userExists ) {
        User* temp = user;
        user = 0;
        userIsShared = true;
        return temp;
    }
    return 0;
}
