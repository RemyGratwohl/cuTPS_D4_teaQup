#include "networklink.h"
#include "../server/ServerCommunication/serializableobjectfactory.h"
#include "../ClientInterface/viewcontrol.h"

NetworkLink::NetworkLink(QObject* parent, ViewControl* vc)
    : QObject(parent), tcpSocket(0), networkSession(0), serverPortNumber(0), viewControl(vc)
{} // handle initialization in the initialize function (to return a success indicator)

bool NetworkLink::sendServerRequest(Message*& message)
{
    if( !establishServerConnection() ) {
        return false;
    }

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
    tcpSocket->connectToHost(serverIP, serverPortNumber);

    // wait for one second to connect
    if(tcpSocket->waitForConnected(1000)) {
        return true;
    } else {
        return false;
    }
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
        viewControl->processMsg(message);
        delete message;
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
        out << SERVER_PORT_NUMBER_FIELD << " " << DEFAULT_SERVER_PORT << "\n";
        out << SERVER_IP_ADDRESS_FIELD << " " << DEFAULT_SERVER_IP;
        serverPortNumber = DEFAULT_SERVER_PORT;
        serverIP = DEFAULT_SERVER_IP;

    } else {
        // if the file does exist, read the server port in from it

        // open the existing file
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
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
