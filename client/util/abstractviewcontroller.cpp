#include "abstractviewcontroller.h"

AbstractViewController::AbstractViewController(ViewControl *vc, ClientDispatcher *d, DEST_TYPE dest) :
    QObject(vc), viewControl(vc), dispatcher(d), ownDest(dest)
{}

bool AbstractViewController::sendData(ACTION_TYPE action, QVector<SerializableQObject *>* data) {
    Message* msg = new DataMessage(ownDest, action, viewControl->getCurrentUser(), data);
    return dispatcher->deliverMsg(msg);
}
