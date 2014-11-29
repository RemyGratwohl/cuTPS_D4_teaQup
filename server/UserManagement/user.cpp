#include "user.h"

User::User(const QString& n) :
    name(n), type(static_cast<TYPE>(0)), identifier(0) {

}

User::User(const QString& n, const TYPE t, const quint16 id) :
    name(n), type(t), identifier(id) {

}

void User::insertToDataStream(QDataStream& ds) const {

}
