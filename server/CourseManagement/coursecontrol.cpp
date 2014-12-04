#include "coursecontrol.h"
#include <QDebug>

CourseControl::CourseControl(QObject* parent)
    : QObject(parent)
{
}

bool CourseControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
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
