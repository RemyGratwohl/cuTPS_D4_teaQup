#include "courseviewcontrol.h"
#include <QDebug>

CourseViewControl::CourseViewControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    courseView = new CourseManagementView(this);
}

bool CourseViewControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "CourseViewControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "CourseViewControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "CourseViewControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "CourseViewControl: received DELETE message.";
        break;
    default:
        qDebug() << "CourseViewControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}

QWidget* CourseViewControl::getView(){
    return courseView;
}
