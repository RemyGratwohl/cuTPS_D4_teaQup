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
* - Establishes and maintains a connection with the client's Network Link
*   (uses TCP/IP to communicate between processes)
*
* Traceability: BD-002
*
* Acknowledgements: None
*/

#include <QObject>
#include <QFile>
#include <QSettings>
#include <QRegExp>
#include <QStringList>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkConfiguration>

#include "../client/ClientCommunication/message.h"

static const QString SERVER_FILE_NAME("ServerPortFile.txt");
static const QString SERVER_PORT_NUMBER_FIELD("SERVER_PORT_NUMBER");
static const quint16 DEFAULT_SERVER_PORT(55505);

class NetworkLink : public QObject
{
    Q_OBJECT
public:
    explicit NetworkLink(QObject *parent = 0);

    bool sendClientResponse(const Message*& message);
    bool initialize();

private slots:
    bool sessionOpened();
    bool handleClientRequest();
    bool readClientRequest();

private:
    QTcpServer *tcpServer;
    QTcpSocket *savedSocket;
    QNetworkSession *networkSession;
    quint16 serverPortNumber;
    QString serverIP;
    quint16 blockSize;

    bool initializeServerPort();
    bool initializeServerIP();
    bool initializeNetworkSession();

};

#endif // NETWORKLINK_H
