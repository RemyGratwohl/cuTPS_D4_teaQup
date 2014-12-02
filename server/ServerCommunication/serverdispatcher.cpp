#include "serverdispatcher.h"

ServerDispatcher::ServerDispatcher(int & argc, char ** argv) :
    QCoreApplication(argc, argv)
{
    networkLink = new NetworkLink(this);
    contentControl = new ContentControl(this);
    courseControl = new CourseControl(this);
    orderControl = new OrderControl(this);
    userControl = new UserControl(this);
    // This most likely doesn't need to be here because the controls are the only classes
    // that interact with storage.
    storageControl = new MainStorageControl(this);
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
