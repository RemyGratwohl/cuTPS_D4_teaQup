#include "clientdispatcher.h"

ClientDispatcher::ClientDispatcher(QObject *parent) :
    QObject(parent), networkLink(0)
{
    networkLink = new NetworkLink(this);
}

bool ClientDispatcher::deliverMsg(const Message*& msg) const {
    // send the message through the network link to the server network link
    networkLink->sendServerRequest(msg);

    // delete message now
    delete msg;
    msg = 0;

    return true;
}
