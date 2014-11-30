#include "serverdispatcher.h"

ServerDispatcher::ServerDispatcher(int & argc, char ** argv) :
    QCoreApplication(argc, argv), networkLink(0)
{
    networkLink = new NetworkLink();
}

bool ServerDispatcher::initialize(void) {
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
