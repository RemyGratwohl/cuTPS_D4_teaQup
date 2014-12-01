#include "serverdispatcher.h"

ServerDispatcher::ServerDispatcher(int & argc, char ** argv) :
    QCoreApplication(argc, argv)
{
    networkLink = new NetworkLink();
    contentControl = new ContentControl();
    courseControl = new CourseControl();
    orderControl = new OrderControl();
    userControl = new UserControl();
    storageControl = new StorageControl();
}

bool ServerDispatcher::initialize(void) {
    if(networkLink->initialize() == false) return false;
    return true;
}

bool ServerDispatcher::deliverMsg(const Message*& msg) const {
    // send the message through the network link to the server network link
    networkLink->sendClientResponse(msg);

    // delete message now
    delete msg;
    msg = 0;

    return true;
}
