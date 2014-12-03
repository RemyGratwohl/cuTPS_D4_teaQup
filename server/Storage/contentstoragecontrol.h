#ifndef CONTENTSTORAGECONTROL_H
#define CONTENTSTORAGECONTROL_H

/*
* contentstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentStorageControl class:
* - handles the content item aspect of the storage system
*
* Traceability: CT-036
*
* Acknowledgements: None
*/

#include <QObject>

class ContentStorageControl : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a fully-initialized ContentStorageControl object
     * in: parent QObject
     * Side Effects: None
     */
    explicit ContentStorageControl(QObject* parent = 0);
};

#endif // CONTENTSTORAGECONTROL_H
