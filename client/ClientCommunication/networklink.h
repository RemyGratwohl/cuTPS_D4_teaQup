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
* - Is the link between the server and client processes
* - Establishes and maintains a connection with the server's Network Link
*   (uses TCP/IP to communicate between processes)
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

    void requestionConnection();
    void handleServerConnection(QByteArray);

private slots:
    //bool sessionOpened();

private:
    bool intializeServerPort();

};

#endif // NETWORKLINK_H
