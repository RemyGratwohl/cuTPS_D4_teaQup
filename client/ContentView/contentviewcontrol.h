#ifndef CONTENTVIEWCONTROL_H
#define CONTENTVIEWCONTROL_H

/*
* contentviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentViewControl class:
* - Manages the ContentView subsystem
*
* Traceability: CT-040
*
* Acknowledgements: None
*/

#include <QObject>
#include "contentview.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"

class ViewControl;

class ContentViewControl : public QObject
{
    Q_OBJECT
public:
    explicit ContentViewControl(ViewControl *viewController = 0, QObject *parent = 0);

    /* Member Function: processMsg
     *   Let the subsystem handle the message
     * in: The message object to handle
     * Side Effects: msg is deleted
     * Return Value: Success indicator
     */
    bool processMsg(Message *msg);

    QWidget* getView();
signals:

public slots:

private:
    ViewControl      *viewController;
    ContentView      *contentView;
};

#endif // CONTENTVIEWCONTROL_H

