#include "ordercontrol.h"
#include <QDebug>
#include "../../client/ClientCommunication/datamessage.h"

OrderControl::OrderControl(ServerDispatcher *d)
    : AbstractManager(d, ORDERING)
{}

bool OrderControl::processMsg(const Message *msg)
{
    bool result = true;
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "OrderControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "OrderControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "OrderControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "OrderControl: received DELETE message.";
        break;
    default:
        qDebug() << "OrderControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}
