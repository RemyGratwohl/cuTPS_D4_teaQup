#ifndef COURSECONTROL_H
#define COURSECONTROL_H

/*
* coursecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* CourseControl class:
* - handles all course operations
*
* Traceability: CT-026
*
* Acknowledgements: None
*/

#include <QObject>
#include "../client/ClientCommunication/message.h"
#include "../client/ClientCommunication/datamessage.h"

class CourseControl : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a fully-initialized CourseControl object
     * in: parent QObject
     * Side Effects: None
     */
    explicit CourseControl(QObject* parent = 0);

    /* Member Function: processMsg
     *   Let the subsystem handle the message
     * in: The message object to handle
     * Side Effects: msg is deleted
     * Return Value: Success indicator
     */
    bool processMsg(Message *msg);
};

#endif // COURSECONTROL_H
