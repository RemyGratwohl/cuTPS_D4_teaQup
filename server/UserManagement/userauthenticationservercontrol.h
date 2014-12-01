#ifndef USERAUTHENTICATIONSERVERCONTROL_H
#define USERAUTHENTICATIONSERVERCONTROL_H

/*
* userauthenticationservercontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserAuthenticationServerControl class:
* - Handles the authentication of users
*
* Traceability: CT-032
*
* Acknowledgements: None
*/

#include <QObject>

class UserAuthenticationServerControl : public QObject
{
    Q_OBJECT
public:
    explicit UserAuthenticationServerControl(QObject* parent = 0);
};

#endif // USERAUTHENTICATIONSERVERCONTROL_H
