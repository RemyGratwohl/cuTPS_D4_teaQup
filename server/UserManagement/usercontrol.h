#ifndef USERCONTROL_H
#define USERCONTROL_H

/*
* usercontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserControl class:
* - handles operations on users
*
* Traceability: CT-033
*
* Acknowledgements: None
*/

#include <QObject>

class UserControl : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a fully-initialized UserControl object
     * in: parent QObject
     * Side Effects: None
     */
    explicit UserControl(QObject* parent = 0);
};

#endif // USERCONTROL_H
