#include "contentviewcontrol.h"
#include <QDebug>

ContentViewControl::ContentViewControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    contentView = new ContentView(this);
}

bool ContentViewControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "ContentViewControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "ContentViewControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "ContentViewControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "ContentViewControl: received DELETE message.";
        break;
    default:
        qDebug() << "ContentViewControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}

QWidget* ContentViewControl::getView(){
     return contentView;
 }
