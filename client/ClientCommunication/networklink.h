#ifndef NETWORKLINK_H
#define NETWORKLINK_H

/*
* networklink.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* NetworkLink class:
* - is the link between the server and client processes
* - uses TCP/IP to communicate between processes
*
* Traceability: BD-002
*
* Acknowledgements: None
*/

#include <QObject>

class NetworkLink : public QObject
{
    Q_OBJECT
public:
    explicit NetworkLink(QObject *parent = 0);

signals:

public slots:

};

#endif // NETWORKLINK_H
