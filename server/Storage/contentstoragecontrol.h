#ifndef CONTENTSTORAGECONTROL_H
#define CONTENTSTORAGECONTROL_H

/*
* contentstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentStorageControl class:
* - handles the content item aspect of the storage system
* - This is a singleton class
*
* Traceability: CT-036
*
* Acknowledgements: None
*/

#include <QObject>
#include <QSharedPointer>
#include "mainstoragecontrol.h"

class ContentStorageControl : public QObject
{
    Q_OBJECT

public:
    /* Static Member Function: getContentStorageControl
     * out: Instance of ContentStorageControl, or nothing, if
     *        the ContentStorageControl instance failed to initialize.
     * Side Effects: None
     * Return Value: True, if the ContentStorageControl object
     *   is properly initialized.
     */
    static bool getContentStorageControl(QSharedPointer<ContentStorageControl>& ptr);

protected:
    /* Constructor
     *   Essentially does nothing
     * Side Effects: None
     */
    ContentStorageControl(void);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

private:
    QSharedPointer<MainStorageControl> mainStorage;

private:
    // Singleton instance
    static QSharedPointer<ContentStorageControl> contentStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // CONTENTSTORAGECONTROL_H
