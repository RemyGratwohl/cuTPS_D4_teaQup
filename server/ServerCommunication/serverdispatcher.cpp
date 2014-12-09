#include "serverdispatcher.h"
#include "../ContentManagement/contentcontrol.h"
#include "../CourseManagement/coursecontrol.h"
#include "../Purchasing/ordercontrol.h"
#include "../UserManagement/usercontrol.h"

ServerDispatcher::ServerDispatcher(int & argc, char ** argv) :
    QCoreApplication(argc, argv)
{
    networkLink = new NetworkLink(this, this);
    courseControl = new CourseControl(this);
    orderControl = new OrderControl(this);
    userControl = new UserControl(this);
    contentControl = new ContentControl(this, courseControl);
}

bool ServerDispatcher::initialize(void)
{
    if(!networkLink->initialize()) return false;
    if(!userControl->initialize()) return false;
    if(!courseControl->initialize()) return false;
    if(!contentControl->initialize()) return false;
    if(!orderControl->initialize()) return false;
    return true;
}

bool ServerDispatcher::deliverMsg(Message*& msg) const
{
    // send the message through the network link to the server network link
    networkLink->sendClientResponse(msg);

    // delete message now
    delete msg;
    msg = 0;

    return true;
}

bool ServerDispatcher::directMsg(Message* msg) const
{
    ErrorMessage* errMsg = qobject_cast<ErrorMessage*>(msg);
    if(errMsg != 0) {
        qDebug() << "Received error message from client: \"" << errMsg->getError() << "\"";
        qDebug() << "Error messages are not dispatched.";
        Message* errorMessage = new ErrorMessage(INVALIDDEST, INVALIDACTION, 0, "Server cannot process an error message.");
        networkLink->sendClientResponse(errorMessage);
        delete errorMessage;
        delete errMsg;
        return true;
    }

    DEST_TYPE msgDest = msg->getDestType();

    DataMessage* dataMsg = qobject_cast<DataMessage*>(msg);
    if(dataMsg != 0) {
        qDebug() << "Received data message from user: " << dataMsg->getUser()->getID();
    }

    // Message routing
    bool result = true;
    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        result = orderControl->processMsg(msg);
        break;
    case USER:
        // userControl handles message
        result = userControl->processMsg(msg);
        break;
    case CONTENT:
        // contentControl handles message
        result = contentControl->processMsg(msg);
        break;
    case COURSE:
        // courseControl handles message
        result = courseControl->processMsg(msg);
        break;
    default:
    {
        QString error = "ServerDispatcher : Unknown message destination.";
        qDebug() << error;
        Message* errorMessage = new ErrorMessage(INVALIDDEST, INVALIDACTION, 0, error);
        networkLink->sendClientResponse(errorMessage);
        delete errorMessage;
        result = true;
        break;
    }
    }

    delete msg;
    return result;
}
