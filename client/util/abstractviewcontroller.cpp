#include "abstractviewcontroller.h"
#include "../ClientCommunication/datamessage.h"
#include <QDebug>

AbstractViewController::AbstractViewController(ViewControl *vc, ClientDispatcher *d, DEST_TYPE dest) :
    QObject(vc), viewControl(vc), dispatcher(d), ownDest(dest), view(0)
{}

void AbstractViewController::sendData(ACTION_TYPE action, QVector<SerializableQObject *>* data) {
    User* userBase = viewControl->getCurrentUser();
    QString name = "";
    User* userMsg = new User(name, static_cast<User::TYPE>(userBase->getType()), static_cast<OBJ_ID_TYPE>(userBase->getID()));
    Message* msg = new DataMessage(ownDest, action, userMsg, data);
    bool result = dispatcher->deliverMsg(msg);
    if( !result ) {
        qDebug() << "AbstractViewController::sendData() : ClientDispatcher::deliverMsg() returned a failure result.";
    }
    delete userMsg;
}

QWidget* AbstractViewController::getView(){
     return view;
 }

void AbstractViewController::closeView(){
    viewControl->closeView();
}
