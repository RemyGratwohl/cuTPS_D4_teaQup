#ifndef ORDERCONTROL_H
#define ORDERCONTROL_H

/*
* ordercontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* OrderControl class:
* - handles the Student user's orders.
*
* Traceability: CT-015
*
* Acknowledgements: None
*/

#include <QObject>

class OrderControl : public QObject
{
    Q_OBJECT
public:
    explicit OrderControl(QObject* parent = 0);
};

#endif // ORDERCONTROL_H
