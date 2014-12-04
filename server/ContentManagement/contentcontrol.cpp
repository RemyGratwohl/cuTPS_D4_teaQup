#include "contentcontrol.h"
#include <QDebug>

ContentControl::ContentControl(ServerDispatcher *d, CourseControl *courseCtrl)
    : QObject(d), dispatcher(d), CourseControl(courseCtrl), contentStorageControl(0)
{}

bool ContentControl::initialize(void) {
    return ContentStorageControl::getContentStorageControl(contentStorageControl);
}

bool ContentControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    if(dataMessage == 0) {
        qDebug() << "ContentControl: Error - received a message which is not of type DataMessage.";
        return false;
    }

    ACTION_TYPE msgAction = dataMessage->getActionType();
    DEST_TYPE msgDest = dataMessage->getDestType();

    if(msgDest != CONTENT) {
        qDebug() << "ContentControl: Error - received a message for another subsystem.";
        return false;
    }

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
        qDebug() << "ContentControl: received unknown message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}
