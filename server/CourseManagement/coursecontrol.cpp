#include "coursecontrol.h"
#include <QDebug>
#include "../../client/ClientCommunication/datamessage.h"

CourseControl::CourseControl(ServerDispatcher *d)
    : AbstractManager(d)
{}

bool CourseControl::processMsg(const Message *msg)
{
    bool result = true;
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "CourseControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "CourseControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "CourseControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "CourseControl: received DELETE message.";
        break;
    default:
        qDebug() << "CourseControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}
