#ifndef MAINSTORAGECONTROL_H
#define MAINSTORAGECONTROL_H

/*
* mainstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* MainStorageControl class:
* - handles all of the aspects of the storage system
* - is the main control for the storage system,
*   interacts with the other storage controls.
*
* Traceability: CT-035
*
* Acknowledgements: None
*/

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include "UserManagement/user.h"

class MainStorageControl : public QObject
{
    Q_OBJECT
public:
    /* Constructor
     *   Creates a fully-initialized MainStorageControl object
     * in: parent QObject
     * Side Effects: None
     */
    explicit MainStorageControl(QObject* parent = 0);

    bool getUser(int userid, User& user, std::string errorMsg);
    QSqlQuery runQuery(QString query);
private:
    QSqlDatabase db;


    // MainStorageControl is not suppsed to have any knowledge of outside StorageControls
    /*
    ContentStorageControl* contentControl;
    CourseStorageControl*  courseControl;
    OrderStorageControl*   orderControl;
    UserStorageControl*    userControl;*/
};

#endif // MAINSTORAGECONTROL_H
