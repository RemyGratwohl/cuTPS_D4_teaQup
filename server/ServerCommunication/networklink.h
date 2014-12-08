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

static const QString SERVER_FILE_NAME("ServerConfigFile.txt");
static const QString SERVER_PORT_NUMBER_FIELD("SERVER_PORT_NUMBER");
static const quint16 DEFAULT_SERVER_PORT(60000);
static const QString SERVER_IP_ADDRESS_FIELD("SERVER_IP_ADDRESS");
static const QString DEFAULT_SERVER_IP("127.0.0.1");

class ServerDispatcher;

class NetworkLink : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a semi-initialized Network object
     * in: parent QObject
     * Side Effects: None
     */
    explicit NetworkLink(QObject *parent = 0, ServerDispatcher* serverDispatch = 0);

    /* Member Function
     *   Sends a message to the client network link
     * in: Message
     * Side Effects: None
     */
    bool sendClientResponse(Message *&message);

    /* Member Function
     *   Fully-initializes the NetworkLink object
     * in: void
     * Side Effects: None
     */
    bool initialize(void);

private slots:
    /* Member Function
     *   Initializes network session using
     *   previous network configuration
     * in: void
     * Side Effects: None
     */
    bool sessionOpened(void);

    /* Member Function
     *   Handles the case where a client process
     *   passes a message to the server process
     * in: void
     * Side Effects: None
     */
    bool handleClientRequest(void);

    /* Member Function
     *   Reads a message from the client
     * in: void
     * Side Effects: None
     */
    bool readClientRequest(void);

private:
    QTcpServer *tcpServer;
    QTcpSocket *savedSocket;
    QNetworkSession *networkSession;
    quint16 serverPortNumber;
    QString serverIP;
    quint16 blockSize;
    ServerDispatcher* serverDispatcher;

    /* Member Function
     *   Initializes server port number
     * in: void
     * Side Effects: None
     */
    bool initializeServerConfig(void);

    /* Member Function
     *   Initializes server IP address
     * in: void
     * Side Effects: None
     */
    bool initializeServerIP(void);

    /* Member Function
     *   Initializes server network session
     *   (TcpServer, NetworkSession)
     * in: void
     * Side Effects: None
     */
    bool initializeNetworkSession(void);

};

#endif // NETWORKLINK_H
