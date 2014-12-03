#include "serverdispatcher.h"

ServerDispatcher::ServerDispatcher(int & argc, char ** argv) :
    QCoreApplication(argc, argv)
{
    networkLink = new NetworkLink(this, this);
    contentControl = new ContentControl(this);
    courseControl = new CourseControl(this);
    orderControl = new OrderControl(this);
    userControl = new UserControl(this);
    storageControl = new MainStorageControl(this);
}

bool ServerDispatcher::initialize(void)
{
    if(networkLink->initialize() == false) return false;
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
        Message* errorMessage = new ErrorMessage(CONTENT, CREATE, new User(), "Server: Hello, Client.");
        networkLink->sendClientResponse(errorMessage);
        delete errMsg;
        return true;
    }

    DEST_TYPE msgDest = msg->getDestType();

    switch(msgDest)
    {
    case ORDERING:
        // orderControl handles message
        break;
    case USER:
        // userControl handles message
        break;
    case CONTENT:
        qDebug() << "\nReceived message with CONTENT destination.\n";
        // contentControl handles message
        break;
    case COURSE:
        // courseControl handles message
        break;
    default:
        break;
    }

    // control systems delete message?
    //delete msg;

    return true;
}
