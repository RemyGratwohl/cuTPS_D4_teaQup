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
* - Singleton class
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
#include <QSharedPointer>

class MainStorageControl : public QObject
{
    Q_OBJECT

    friend class CourseStorageControl;
    friend class ContentStorageControl;
    friend class UserStorageControl;
    friend class OrderStorageControl;

protected:
    /* Constructor
     *   Essentially does nothing
     * Side Effects: None
     */
    MainStorageControl(void);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

    /* Static Member Function: getMainStorageControl
     * out: Instance of MainStorageControl, or nothing, if
     *        the MainStorageControl instance failed to initialize.
     * Side Effects: None
     * Return Value: True, if the MainStorageControl object
     *   is properly initialized.
     */
    static bool getMainStorageControl(QSharedPointer<MainStorageControl>& ptr);

public:

    /* Member Function: runQuery
     * in: QString containing the query to be executed
     * Side Effects: Depending on the query, database may be modified.
     * Return Value: QSqlQuery containing the result set
     */
    QSqlQuery runQuery(QString query);

private:
    QSqlDatabase db;

    void runSqlScript();

private:
    // Singleton instance
    static QSharedPointer<MainStorageControl> mainStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // MAINSTORAGECONTROL_H
