#include "usercontrol.h"
#include <QDebug>
#include "../../client/ClientCommunication/datamessage.h"

UserControl::UserControl(ServerDispatcher *d)
    : AbstractManager(d, USER), userStorageControl(0)
{}

bool UserControl::initialize(void) {
    return UserStorageControl::getUserStorageControl(userStorageControl);
}

bool UserControl::processMsg(const Message *msg)
{
    QString error;
    ACTION_TYPE msgAction = INVALIDACTION;
    DEST_TYPE msgDest = INVALIDDEST;
    User* user = msg->getUser();

    // Input validation concerning the message dispatching
    // ---------------------------------------------------
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        error = "UserControl: Error - received a message which is not of type DataMessage.";
        return sendError(msgDest, msgAction, user, error);
    }

    msgAction = dataMessage->getActionType();
    msgDest = dataMessage->getDestType();

    if(msgDest != ownDest) {
        error = "UserControl: Error - received a message for another subsystem.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    if( data->size() != 0 ) {
        error =  "UserControl: Error - Message data vector has a length other than 0."
                 " Presently, all messages are expected to be empty.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    bool result = true;
    QVector<SerializableQObject*>* output = 0;
    User* userOut = 0;

    switch(msgAction)
    {

    case RETRIEVE:
        qDebug() << "UserControl: received RETRIEVE message.";
        result = authenticateUser(user, userOut, error);
        if( result ) {
            output = new QVector<SerializableQObject*>();
        }
        break;

    default:
        error =  "UserControl: Unexpected message action type.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Handle errors
    if( !result ) {
        return sendError(msgDest, msgAction, user, error);
    }

    // Dispatch data, if any exists
    if( output != 0 ) {
        return sendData(msgAction, userOut, output);
    } else {
        return sendSuccess(msgAction, userOut);
    }
}

bool UserControl::authenticateUser(const User* userIn, User*& userOut, QString& errorMsg) {
    OBJ_ID_TYPE id = userIn->getID();
    return userStorageControl->getUser(id, userOut, errorMsg);
}

