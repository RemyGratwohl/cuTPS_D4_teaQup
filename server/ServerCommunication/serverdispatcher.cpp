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
        qDebug() << errMsg->getError();
        Message* errorMessage = new ErrorMessage(CONTENT, CREATE, new User((quint64)0), "Server: Can't process an error message.");
        networkLink->sendClientResponse(errorMessage);
        delete errMsg;
        return true;
    }

    QVector<SerializableQObject *>* data = new QVector<SerializableQObject *>();
    Message* newMessage = new DataMessage(CONTENT, DELETE, new User((quint64)265), data);
    networkLink->sendClientResponse(newMessage);

    DEST_TYPE msgDest = msg->getDestType();

    DataMessage* dataMsg = qobject_cast<DataMessage*>(msg);
    if(dataMsg != 0) {
        qDebug() << "Received data message from user: " << dataMsg->getUser()->getID();
    }

    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        return orderControl->processMsg(msg);
        break;
    case USER:
        // userControl handles message
        return userControl->processMsg(msg);
        break;
    case CONTENT:
        // contentControl handles message
        return contentControl->processMsg(msg);
        break;
    case COURSE:
        // courseControl handles message
        return courseControl->processMsg(msg);
        break;
    default:
        return false;
        break;
    }

    return false;
}
