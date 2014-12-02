#include "mainstoragecontrol.h"

using namespace std;

MainStorageControl::MainStorageControl(QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    // Database path may need to also be configurable
    db.setDatabaseName("../../cuTPS_D4_teaQup/cuTPSDB");
}


bool MainStorageControl::getUser(int userid, User& user, string errorMsg){
    // Query: select * from users where userid = userid;

    // Send query to DB TODO: Function for running queries
    // Get back the result
    // Is the error message neccessary for this one? Maybe not.
    // Set User to null if not found - better yet return false, set user to null and errorMsg = '';
    // Error message is useful if there's a db connection problem.
    // Why not just return a string instead of a boolean?
    // Otherwise create a new user, set user equal to newUser return true.
}


QSqlQuery MainStorageControl::runQuery(QString query){
    if(db.open()){
            qDebug()  << "Database connected!";
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
