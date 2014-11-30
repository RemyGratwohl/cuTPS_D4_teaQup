#include "networklink.h"

NetworkLink::NetworkLink(QObject* parent)
    : QObject(parent), tcpSocket(0), networkSession(0), serverPortNumber(0)
{
    // order is important here
    initializeServerPort();
    initializeNetworkSession();

    tcpSocket = new QTcpSocket(this);
    //connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(handleServerResponse()));
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
