#include "clientdispatcher.h"
#include "ClientInterface/viewcontrol.h"

ClientDispatcher::ClientDispatcher(QObject *parent,
                                   ViewControl* vc) :
    QObject(parent),
    viewControl(vc)
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
    bool result = viewControl->processMsg(msg);
    delete msg;
    return result;
}

bool ClientDispatcher::initialize()
{
    networkLink = new NetworkLink(this, this);
    if(networkLink->initialize() == false) return false;

    return true;
}
