#include "abstractviewcontroller.h"
#include "../ClientCommunication/datamessage.h"
#include <QDebug>

AbstractViewController::AbstractViewController(ViewControl *vc, ClientDispatcher *d, DEST_TYPE dest) :
    QObject(vc), viewControl(vc), dispatcher(d), ownDest(dest), view(0)
{}

void AbstractViewController::sendData(ACTION_TYPE action, QVector<SerializableQObject *>* data) {
    Message* msg = new DataMessage(ownDest, action, viewControl->getCurrentUser(), data);
    bool result = dispatcher->deliverMsg(msg);
    if( !result ) {
        qDebug() << "AbstractViewController::sendData() : ClientDispatcher::deliverMsg() returned a failure result.";
    }
}

QWidget* AbstractViewController::getView(){
     return view;
 }

void AbstractViewController::closeView(){
    viewControl->closeView();
}
