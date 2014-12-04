#include <QCoreApplication>
#include "Storage/mainstoragecontrol.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /* TODO make MainStorageControl constructor and initialization functions protected
     * once finished with this test code.
     *
     * TODO Also put user querying functionality in the UserStorageControl class.
     */
    MainStorageControl* storage = new MainStorageControl();
    storage->initialize();
    QString string = "Select * from users";
    storage->runQuery(string);
}
