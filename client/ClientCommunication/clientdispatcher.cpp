#include "clientdispatcher.h"

ClientDispatcher::ClientDispatcher(QObject *parent,
                                   ContentViewControl* contentControl,
                                   CourseViewControl* courseControl,
                                   ShoppingCartControl* shoppingControl) :
    QObject(parent),
    contentViewControl(contentControl),
    courseViewControl(courseControl),
    shoppingCartControl(shoppingControl)
{}

bool ClientDispatcher::deliverMsg(Message*& msg) const {
    // send the message through the network link to the server network link
    networkLink->sendServerRequest(msg);

    // delete message now
    delete msg;
    msg = 0;

    return true;
}

bool ClientDispatcher::directMsg(Message* msg) const
{
    ErrorMessage* errMsg = qobject_cast<ErrorMessage*>(msg);
    if(errMsg != 0) {
        qDebug() << errMsg->getError();
        delete errMsg;
        return true;
    }

    DEST_TYPE msgDest = msg->getDestType();

    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        return shoppingCartControl->processMsg(msg);
        break;
    case USER:
        // userControl handles message
        //return userControl->processMsg(msg);
        break;
    case CONTENT:
        // contentControl handles message
        return contentViewControl->processMsg(msg);
        break;
    case COURSE:
        // courseControl handles message
        return courseViewControl->processMsg(msg);
        break;
    default:
        return false;
        break;
    }

    return false;
}

bool ClientDispatcher::initialize()
{
    networkLink = new NetworkLink(this, this);
    if(networkLink->initialize() == false) return false;

    return true;
}
