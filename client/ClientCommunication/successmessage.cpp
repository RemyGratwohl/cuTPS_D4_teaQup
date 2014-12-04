#include "successmessage.h"

SuccessMessage::SuccessMessage(void) :
    Message(), info(), reference(0), referenceValidity(false)
{}

SuccessMessage::SuccessMessage(DEST_TYPE dt, ACTION_TYPE at, User* u, const QString& i,
             const OBJ_ID_TYPE& r, bool b) :
Message(dt, at, u), info(i), reference(r), referenceValidity(b)
{}

bool SuccessMessage::getReference(OBJ_ID_TYPE &r) const {
    if( referenceValidity ) {
        r = reference;
    }
    return referenceValidity;
}

void SuccessMessage::insertToDataStream(QDataStream& ds) const {
    Message::insertToDataStream(ds, SUCCESSMESSAGE);
}
