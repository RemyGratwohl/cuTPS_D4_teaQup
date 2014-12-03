#include "user.h"

User::User(void) : name(), type(User::STUDENT), identifier(0) {}

User::User(const quint16 id) :
    name(), type(static_cast<TYPE>(0)), identifier(id) {

}

User::User(const QString& n, const TYPE t, const quint16 id) :
    name(n), type(t), identifier(id) {

}

void User::insertToDataStream(QDataStream& ds) const {
        SerializableQObject::insertToDataStream(ds, USEROBJ);
}

bool User::isOfType(const TYPE t) const {
    return (t == type);
}
