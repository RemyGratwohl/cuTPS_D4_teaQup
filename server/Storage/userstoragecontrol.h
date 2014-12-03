#ifndef USERSTORAGECONTROL_H
#define USERSTORAGECONTROL_H

/*
* userstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserStorageControl class:
* - handles the user aspect of the storage system
*
* Traceability: CT-038
*
* Acknowledgements: None
*/

#include <QObject>

class UserStorageControl : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a fully-initialized UserStorageControl object
     * in: parent QObject
     * Side Effects: None
     */
    explicit UserStorageControl(QObject* parent = 0);
};

#endif // USERSTORAGECONTROL_H
