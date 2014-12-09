#include "user.h"

User::User(void) : name(), type(User::INVALID), identifier(0) {}

User::User(const OBJ_ID_TYPE id) :
    name(), type(User::INVALID), identifier(id) {
}

User::User(const QString& n, const TYPE t, const OBJ_ID_TYPE id) :
    name(n), type(t), identifier(id) {

}

void User::insertToDataStream(QDataStream& ds) const {
    SerializableQObject::insertToDataStream(ds, USEROBJ);
}

bool User::isOfType(const TYPE t) const {
    return (t == type);
}
