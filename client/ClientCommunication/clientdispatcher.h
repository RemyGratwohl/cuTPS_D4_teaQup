#ifndef CLIENTDISPATCHER_H
#define CLIENTDISPATCHER_H

/*
* clientdispatcher.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ClientDispatcher class:
* - Responsbile for passing around Message objects to the other client-side subsystems.
*
* Traceability: CT-029
*
* Acknowledgements: None
*/

#include <QObject>
#include "ClientCommunication/message.h"

class ClientDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit ClientDispatcher(QObject *parent = 0);
    bool deliverMsg(Message message);

signals:

public slots:

};

#endif // CLIENTDISPATCHER_H
