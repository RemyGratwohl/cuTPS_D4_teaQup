#include <QCoreApplication>
#include "ServerCommunication/networklink.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NetworkLink* link = new NetworkLink();

    return a.exec();
}
