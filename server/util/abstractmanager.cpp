#include "abstractmanager.h"
#include "../../client/ClientCommunication/successmessage.h"
#include "../../client/ClientCommunication/errormessage.h"
#include "../../client/ClientCommunication/datamessage.h"

AbstractManager::AbstractManager(ServerDispatcher *d, DEST_TYPE dest) :
    QObject(d), dispatcher(d), ownDest(dest)
{}

bool AbstractManager::sendError(DEST_TYPE dest, ACTION_TYPE action, User* user, const QString& error) {
    qDebug() << error;
    Message* outputError = new ErrorMessage(dest, action, user, error);
    return dispatcher->deliverMsg(outputError);
}

bool AbstractManager::sendData(ACTION_TYPE action, User* user, QVector<SerializableQObject *>* data) {
    Message* msg = new DataMessage(ownDest, action, user, data);
    return dispatcher->deliverMsg(msg);
}

bool AbstractManager::sendSuccess(ACTION_TYPE action, User* user, const QString& info,
             const OBJ_ID_TYPE& reference, bool hasReference) {
    Message* msg = new SuccessMessage(ownDest, action, user, info, reference, hasReference);
    return dispatcher->deliverMsg(msg);
}
