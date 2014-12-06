#include "userauthenticationcontrol.h"
#include "../ClientCommunication/datamessage.h"
#include <QDebug>

UserAuthenticationControl::UserAuthenticationControl(ViewControl *vc, ClientDispatcher *d) :
    AbstractViewController(vc, d, USER), isAuthenticated(false)
{}

bool UserAuthenticationControl::requestAuthentication(OBJ_ID_TYPE id) {
    User* user = new User(id);
    Message* msg = new DataMessage(ownDest, RETRIEVE, user, new QVector<SerializableQObject*>());
    bool result = dispatcher->deliverMsg(msg);
    delete user;
    return result;
}

bool UserAuthenticationControl::processMsg(Message* msg) {
    QString error;
    ACTION_TYPE msgAction = INVALIDACTION;
    DEST_TYPE msgDest = INVALIDDEST;

    msgAction = msg->getActionType();
    msgDest = msg->getDestType();

    if(msgDest != ownDest) {
        qDebug() << "UserAuthenticationControl: Error - received a message for another subsystem.";
        return false;
    }

    if(isAuthenticated) {
        qDebug() << "UserAuthenticationControl: Error - Already authenticated.";
        return false;
    }

    // Validate the type of message
    // ----------------------------
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        qDebug() << "UserAuthenticationControl: Error - received a message which is not of type DataMessage.";
        return false;
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    if( data->size() != 0 ) {
        error =  "UserAuthenticationControl: Error - Message data vector has a length other than 0."
                 " Presently, all messages are expected to be empty.";
        return false;
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    bool result = true;

    switch(msgAction)
    {

    case RETRIEVE:
    {
        qDebug() << "UserAuthenticationControl: received RETRIEVE message.";
        User* user = msg->extractUser();
        result = viewControl->setCurrentUser(user);
        isAuthenticated = true;
        break;
    }

    case CREATE:
    case UPDATE:
    case DELETE:
    case INVALIDACTION:
    default:
        qDebug() << "UserAuthenticationControl: Unexpected message action type.";
        result = false;
        break;
    }

    return result;
}
