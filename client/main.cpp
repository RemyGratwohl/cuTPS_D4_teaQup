#include <QApplication>
#include "ClientInterface/viewcontrol.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ViewControl vc;

    return a.exec();
}
