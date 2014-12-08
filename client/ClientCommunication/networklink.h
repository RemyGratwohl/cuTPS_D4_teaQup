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
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkSession>
#include <QRegExp>
#include <QStringList>
#include <QFile>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkConfiguration>
#include <QSettings>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

#include "message.h"
#include "../server/ServerCommunication/serializableqobject.h"
#include "../server/ServerCommunication/messageroutingtypes.h"

static const QString SERVER_FILE_NAME("ServerConfigFile.txt");
static const QString SERVER_PORT_NUMBER_FIELD("SERVER_PORT_NUMBER");
static const quint16 DEFAULT_SERVER_PORT(55505);
static const QString SERVER_IP_ADDRESS_FIELD("SERVER_IP_ADDRESS");
static const QString DEFAULT_SERVER_IP("127.0.0.1");

class ClientDispatcher;

class NetworkLink : public QObject
{
    Q_OBJECT
public:
    explicit NetworkLink(QObject *parent = 0, ClientDispatcher* clientDispatch = 0);

    bool sendServerRequest(Message *&message);
    bool initialize();

private slots:
    bool sessionOpened();
    bool readServerResponse();

private:
    QTcpSocket *tcpSocket;
    QNetworkSession *networkSession;
    quint16 serverPortNumber;
    QString serverIP;
    quint16 blockSize;
    ClientDispatcher* clientDispatcher;

    bool initializeServerPort();
    bool initializeNetworkSession();

    bool establishServerConnection();

};

#endif // NETWORKLINK_H
