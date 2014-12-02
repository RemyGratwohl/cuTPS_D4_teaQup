#include <QCoreApplication>
#include "Storage/mainstoragecontrol.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*MainStorageControl* storage = new MainStorageControl();
    storage->runQuery("Select * from users");*/
    return a.exec();
}
