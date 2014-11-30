#include "clientdispatcher.h"

ClientDispatcher::ClientDispatcher(QObject *parent) :
    QObject(parent)
{
}

bool ClientDispatcher::deliverMsg(const Message*& msg) const {

}
