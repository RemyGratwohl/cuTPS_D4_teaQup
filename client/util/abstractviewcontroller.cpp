#include "abstractviewcontroller.h"
#include <QDebug>

AbstractViewController::AbstractViewController(ViewControl *vc, ClientDispatcher *d, DEST_TYPE dest) :
    QObject(vc), viewControl(vc), dispatcher(d), ownDest(dest)
{}

void AbstractViewController::sendData(ACTION_TYPE action, QVector<SerializableQObject *>* data) {
    Message* msg = new DataMessage(ownDest, action, viewControl->getCurrentUser(), data);
    bool result = dispatcher->deliverMsg(msg);
    if( !result ) {
        qDebug() << "AbstractViewController::sendData() : ClientDispatcher::deliverMsg() returned a failure result.";
    }
}
