#ifndef USERVIEWCONTROL_H
#define USERVIEWCONTROL_H

/*
* userviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserViewControl class:
* - Manages the displaying and modification of the Users done by Administrators
*
* Traceability: CT-034
*
* Acknowledgements: None
*/

#include <QObject>

class UserViewControl : public QObject
{
    Q_OBJECT
public:
    explicit UserViewControl(QObject *parent = 0);

signals:

public slots:

};

#endif // USERVIEWCONTROL_H
