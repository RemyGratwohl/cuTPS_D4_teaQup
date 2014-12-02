#include <QCoreApplication>
#include "Storage/mainstoragecontrol.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MainStorageControl* storage = new MainStorageControl();
    QString string = "Select * from users";
    storage->runQuery(string);
}
