#include "serverdispatcher.h"

ServerDispatcher::ServerDispatcher(int & argc, char ** argv) :
QCoreApplication(argc, argv)
{

}

bool ServerDispatcher::initialize(void) {

}

bool ServerDispatcher::deliverMsg(const Message*& msg) const {

}
