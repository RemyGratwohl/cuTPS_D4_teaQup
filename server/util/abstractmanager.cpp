#include "abstractmanager.h"

AbstractManager::AbstractManager(ServerDispatcher *d) :
    QObject(d), dispatcher(d)
{
}
