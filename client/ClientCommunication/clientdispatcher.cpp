#include "clientdispatcher.h"

ClientDispatcher::ClientDispatcher(QObject *parent,
                                   ContentViewControl* contentControl,
                                   CourseViewControl* courseControl,
                                   ShoppingCartControl* shoppingControl,
                                   UserViewControl* userControl) :
    QObject(parent),
    contentViewControl(contentControl),
    courseViewControl(courseControl),
    shoppingCartControl(shoppingControl),
    userViewControl(userControl)
{}

bool ClientDispatcher::deliverMsg(Message*& msg) const {
    // send the message through the network link to the server network link
    networkLink->sendServerRequest(msg);

    // delete message now
    delete msg;
    msg = 0;

    return true;
}

bool ClientDispatcher::initialize()
{
    networkLink = new NetworkLink(this);
    if(networkLink->initialize() == false) return false;

    return true;
}
