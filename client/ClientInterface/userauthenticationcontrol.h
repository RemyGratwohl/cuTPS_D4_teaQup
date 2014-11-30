#ifndef USERAUTHENTICATIONCONTROL_H
#define USERAUTHENTICATIONCONTROL_H

/*
* userauthenticationcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserAuthenticationControl class:
* - Manages the authentication request for the client
*
* Traceability: CT-030
*
* Acknowledgements: None
*/

#include <QObject>

class UserAuthenticationControl : public QObject
{
    Q_OBJECT
public:
    explicit UserAuthenticationControl(QObject *parent = 0);

signals:

public slots:

};

#endif // USERAUTHENTICATIONCONTROL_H
