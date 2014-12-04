#include "usercontrol.h"
#include <QDebug>

UserControl::UserControl(QObject *parent)
    : QObject(parent)
{
}

bool UserControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "UserControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "UserControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "UserControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "UserControl: received DELETE message.";
        break;
    default:
        qDebug() << "UserControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}
