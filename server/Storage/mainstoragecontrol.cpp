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
    db = QSqlDatabase::addDatabase("QSQLITE");
    // Database path may need to also be configurable
    db.setDatabaseName("../../cuTPS_D4_teaQup/cuTPSDB");

    return true;
}


/*bool MainStorageControl::getUser(int userid, User& user, string errorMsg){
    // Query: select * from users where userid = userid;

    // Send query to DB TODO: Function for running queries
    // Get back the result
    // Is the error message neccessary for this one? Maybe not.
    // Set User to null if not found - better yet return false, set user to null and errorMsg = '';
    // Error message is useful if there's a db connection problem.
    // Why not just return a string instead of a boolean?
    // Otherwise create a new user, set user equal to newUser return true.
    return false;
}*/


QSqlQuery MainStorageControl::runQuery(QString query){
    if(db.open()){
            qDebug()  << "Database connected!";
            if(db.tables().isEmpty())
            {
                qDebug() << "Database is empty! Running script.";
                runSqlScript();
            }
            qDebug() << query;

            // Retrieve info

            QSqlQuery q(query);

            if(q.exec()){
                qDebug() << "Query Executed!";
                db.close();
                return q;
            }
            else{
                qDebug() << "Query failed!";
                qDebug() << q.lastError();
                db.close();
                return q;
            }
        }
        else{
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
