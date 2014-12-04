#include "networklink.h"
#include "ClientCommunication/clientdispatcher.h"
#include "../server/ServerCommunication/serializableobjectfactory.h"

NetworkLink::NetworkLink(QObject* parent, ClientDispatcher *clientDispatch)
    : QObject(parent), tcpSocket(0), networkSession(0), serverPortNumber(0), clientDispatcher(clientDispatch)
{} // handle initialization in the initialize function (to return a success indicator)

bool NetworkLink::sendServerRequest(Message*& message)
{
    establishServerConnection();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    SerializableObjectFactory::serializeObject(out,*message);
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
    return true;
}

bool NetworkLink::establishServerConnection()
{
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress::LocalHost, serverPortNumber);
    return true;
}

bool NetworkLink::readServerResponse()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return false;

        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return false;

    SerializableQObject *preNewItem = 0;
    SerializableObjectFactory::deserializeObject(in,preNewItem);
    Message* message = qobject_cast<Message*>(preNewItem);

    if(message != 0) {
        clientDispatcher->directMsg(message);
        return true;
    } else {
        qDebug() << "Failed object read.";
    }
    return false;
}

bool NetworkLink::initializeServerPort()
{
    // the file that will contain the server port
    QFile file(SERVER_FILE_NAME);

    // if the file doesn't exist, simply create one and populate it with the DEFAULT_SERVER_PORT
    if(!file.exists())
    {
        // create the file
        if(file.open(QIODevice::WriteOnly | QIODevice::Text) == false) {
            return false; // file cannot be modified, return unsuccessfully
        }

        // write the server port to the newly created file
        QTextStream out(&file);
        // sample output: SERVER_PORT_NUMBER 15505
        out << SERVER_PORT_NUMBER_FIELD << " " << DEFAULT_SERVER_PORT;
        serverPortNumber = DEFAULT_SERVER_PORT;

    } else {
        // if the file does exist, read the server port in from it

        // open the existing file
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
            return false; // file cannot be opened, return unsuccessfully
        }

        QTextStream in(&file);

        QRegExp rx(SERVER_PORT_NUMBER_FIELD);

        while(!in.atEnd()) {
            QString fileString = in.readLine();
            // if the line matches the port number field, parse it for the port number
            if(rx.indexIn(fileString) != -1) {
                QStringList list = fileString.split(QRegExp("\\s"));
                // save the port number (the second entry if the first is the description
                serverPortNumber = list.at(1).toUShort();
            }
        }
    }

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

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        networkSession->open();
    }
    return true;
}

bool NetworkLink::sessionOpened()
{
    // Save the used configuration
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
    return true;
}

bool NetworkLink::initialize()
{
    // order is important here
    if(initializeServerPort() == false) return false;
    if(initializeNetworkSession() == false) return false;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readServerResponse()));

    return true;
}
