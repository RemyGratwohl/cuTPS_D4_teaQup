#ifndef COURSEVIEWCONTROL_H
#define COURSEVIEWCONTROL_H

/*
* courseviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* CourseViewControl class:
* - Manages the CourseView subsystem.
*
* Traceability: CT-027
*
* Acknowledgements: None
*/

#include <QObject>
#include "coursemanagementview.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"

class ViewControl;

class CourseViewControl : public QObject
{
    Q_OBJECT
public:
    explicit CourseViewControl(ViewControl *viewController = 0, QObject *parent = 0);

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
    ViewControl          *viewController;
    CourseManagementView *courseView;
};

#endif // COURSEVIEWCONTROL_H

