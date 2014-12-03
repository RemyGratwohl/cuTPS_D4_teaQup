#include "contentcontrol.h"
#include <QDebug>

ContentControl::ContentControl(QObject *parent)
    : QObject(parent)
{
}

bool ContentControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "ContentControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "ContentControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "ContentControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "ContentControl: received DELETE message.";
        break;
    default:
        qDebug() << "ContentControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}
