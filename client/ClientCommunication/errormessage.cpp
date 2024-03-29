#include "errormessage.h"

ErrorMessage::ErrorMessage() :
    Message(), error()
{}

ErrorMessage::ErrorMessage(DEST_TYPE dt, ACTION_TYPE at, User* u, const QString& error_) :
    Message(dt, at, u), error(error_)
{}

void ErrorMessage::insertToDataStream(QDataStream& ds) const {
    Message::insertToDataStream(ds, ERRORMESSAGE);
}
