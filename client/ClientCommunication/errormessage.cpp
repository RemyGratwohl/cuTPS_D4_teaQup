#include "errormessage.h"

ErrorMessage::ErrorMessage(DEST_TYPE dt, ACTION_TYPE at, const QString& error_) :
    Message(dt, at), error(error_)
{
}

void ErrorMessage::insertToDataStream(QDataStream& ds) const {

}
