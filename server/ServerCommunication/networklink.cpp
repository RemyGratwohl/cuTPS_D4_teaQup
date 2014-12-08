#include "networklink.h"
#include "serializableobjectfactory.h"
#include "serverdispatcher.h"

NetworkLink::NetworkLink(QObject *parent, ServerDispatcher* serverDispatch)
    : QObject(parent), tcpServer(0), networkSession(0), serverPortNumber(0), blockSize(0), serverDispatcher(serverDispatch)
{} // handle initialization in the initialize function (to return a success indicator)

bool NetworkLink::sendClientResponse(Message *&message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    SerializableObjectFactory::serializeObject(out,*message); // read in the message and send it to the client
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QTcpSocket *clientConnection = savedSocket;
    connect(clientConnection, SIGNAL(disconnected()),
    clientConnection, SLOT(deleteLater()));
    clientConnection->write(block);
    clientConnection->disconnectFromHost();

    return true;
}

bool NetworkLink::handleClientRequest()
{
    QTcpSocket *tcpSocket = tcpServer->nextPendingConnection();
    savedSocket = tcpSocket;
    blockSize = 0;
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readClientRequest()));
    return true;
}

bool NetworkLink::readClientRequest()
{
    QTcpSocket *tcpSocket = savedSocket;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return false;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return false;

    SerializableQObject* theObj;
    SerializableObjectFactory::deserializeObject(in,theObj);

    // the client message
    Message* newMessage = qobject_cast<Message*>(theObj);

    if(newMessage != 0) {
        serverDispatcher->directMsg(newMessage);

        return true;
    } else {
        qDebug() << "Failed object read.";
    }
    return false;
}

bool NetworkLink::initializeServerConfig()
{
    // the file that will contain the server port
    QFile file(SERVER_FILE_NAME);

    // if the file doesn't exist, simply create one and populate it with the DEFAULT_SERVER_PORT
    if(!file.exists())
    {
        // create the file
        if(file.open(QIODevice::WriteOnly | QIODevice::Text) == false) {
            // if the file cannot be written to, notify the user and return false
            qCritical() << tr("ServerRequest failed to initialize the server port.\nCannot write to file %1:\n%2.")
                               .arg(SERVER_FILE_NAME)
                               .arg(file.errorString());
            return false; // file cannot be modified, return unsuccessfully
        }

        // write the server port to the newly created file
        QTextStream out(&file);
        // sample output: SERVER_PORT_NUMBER 15505
        out << SERVER_PORT_NUMBER_FIELD << " " << DEFAULT_SERVER_PORT << "\n";
        out << SERVER_IP_ADDRESS_FIELD << " " << DEFAULT_SERVER_IP;
        serverPortNumber = DEFAULT_SERVER_PORT;
        serverIP = DEFAULT_SERVER_IP;

    } else {
        // if the file does exist, read the server port in from it

        // open the existing file
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
            qCritical() << tr("ServerRequest failed to initialize the server port.\nCannot read file %1:\n%2.")
                               .arg(SERVER_FILE_NAME)
                               .arg(file.errorString());
            return false; // file cannot be opened, return unsuccessfully
        }

        QTextStream in(&file);

        QRegExp rx_port(SERVER_PORT_NUMBER_FIELD);
        QRegExp rx_ip(SERVER_IP_ADDRESS_FIELD);

        while(!in.atEnd()) {
            QString fileString = in.readLine();
            // if the line matches the field, parse it for the value
            if(rx_port.indexIn(fileString) != -1) {
                QStringList list = fileString.split(QRegExp("\\s"));
                // save the port number (the second entry if the first is the description
                for(int i = 0; i < list.size(); ++i) {
                    if(SERVER_PORT_NUMBER_FIELD.compare(list.at(i)) == 0) {
                        serverPortNumber = list.at(i + 1).toUShort();
                    }
                }
            }

            if(rx_ip.indexIn(fileString) != -1) {
                QStringList list = fileString.split(QRegExp("\\s"));
                // save the ip address (the second entry if the first is the description
                for(int i = 0; i < list.size(); ++i) {
                    if(SERVER_IP_ADDRESS_FIELD.compare(list.at(i)) == 0) {
                        serverIP = list.at(i + 1);
                    }
                }
            }
        }
    }
    return true;
}

bool NetworkLink::initializeServerIP()
{
    tcpServer = new QTcpServer(this);
    // set the server ip address
    //serverIP = QHostAddress(serverIP).toString();

    if (!tcpServer->listen(QHostAddress(serverIP), serverPortNumber)) {
        qCritical() << tr("Unable to start the server: %1.")
                           .arg(tcpServer->errorString());
        tcpServer->close();
        return false;
    }
    qDebug() << "IP:  " << serverIP << "\nPort:" << QString::number(tcpServer->serverPort());
    return true;
}

bool NetworkLink::initializeNetworkSession()
{
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {

        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        // set up the network session using the discovered network configuration
        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        networkSession->open();
    } else {
        sessionOpened();
    }
    return true;
}

bool NetworkLink::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }
    return true;
}

bool NetworkLink::initialize()
{
    // order is important here
    if(initializeServerConfig() == false) return false;
    if(initializeNetworkSession() == false) return false;
    if(initializeServerIP() == false) return false;

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(handleClientRequest()));
    return true;
}
