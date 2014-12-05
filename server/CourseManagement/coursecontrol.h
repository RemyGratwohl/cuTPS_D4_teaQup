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

#include "../util/abstractmanager.h"

class CourseControl : public AbstractManager
{
    Q_OBJECT
public:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * Side Effects: None
     * All input pointers are treated as shared pointers.
     */
    CourseControl(ServerDispatcher *dispatcher);

    /* Member Function: processMsg
     *   Handles a message received from the dispatcher,
     *     possibly resulting in messages sent back through the dispatcher
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    virtual bool processMsg(const Message* msg);
};

#endif // COURSECONTROL_H
