#include "ClientInterface/loginwindow.h"
#include <QApplication>
#include "ClientCommunication/networklink.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NetworkLink* link = new NetworkLink();

    LoginWindow lw;
    lw.show();

    return a.exec();
}
