#include "mainstoragecontrol.h"
#include <QStringList>
#include <QFile>

using namespace std;

QSharedPointer<MainStorageControl> MainStorageControl::mainStorage(new MainStorageControl());

bool MainStorageControl::isInitialized = false;
bool MainStorageControl::initializationAttempted = false;

bool MainStorageControl::getMainStorageControl(QSharedPointer<MainStorageControl>& ptr) {
    if( !initializationAttempted ) {
        initializationAttempted = true;
        isInitialized = mainStorage->initialize();
    }
    if( isInitialized ) {
        ptr = mainStorage;
    }
    return isInitialized;
}

MainStorageControl::MainStorageControl(void)
{}

bool MainStorageControl::initialize(void)
{
    // TODO: Database name + sql script to be configurable
    db = QSqlDatabase::addDatabase("QSQLITE");
    // Database path may need to also be configurable
    db.setDatabaseName("../../cuTPS_D4_teaQup/cuTPSDB");

    return true;
}

// The debug statements will remain until the entire database storage system is complete
// If they're bothering you, set bool DEBUG to false.
QSqlQuery MainStorageControl::runQuery(QString query){
    bool DEBUG = true;
    if(db.open()){
            if(DEBUG)
                qDebug()  << "Database connected!";
            if(db.tables().isEmpty())
            {
                // Shouldn't run very often, so not determined by DEBUG
                qDebug() << "Database is empty! Running script.";
                runSqlScript();
            }

            if(DEBUG)
                qDebug() << query;

            // Retrieve info

            QSqlQuery q(query);

            if(q.exec()){
                if(DEBUG)
                    qDebug() << "Query Executed!";
                db.close();
                return q;
            }
            else{
                if(DEBUG){
                    qDebug() << "Query failed!";
                    qDebug() << q.lastError();
                }
                db.close();
                return q;
            }
        }
        else{
            if(DEBUG)
                qDebug()  << "Database failed to open!";
            QSqlQuery q(query);
            return q;
        }
}

void MainStorageControl::runSqlScript() {
    QFile schemaFile("../../cuTPS_D4_teaQup/cuTPS.sql");

    schemaFile.open(QFile::ReadOnly);

    QStringList schemaList = QString(schemaFile.readAll()).split(";");
    foreach(const QString schemaTable, schemaList)
    {
        if(!schemaTable.trimmed().isEmpty())
        {
            db.exec(schemaTable);
        }
    }
    schemaFile.close();

    if(db.tables().isEmpty())
        qDebug() << "Script running failed.";
    else
        qDebug() << "Script successful!";
}
