#ifndef COURSESTORAGECONTROL_H
#define COURSESTORAGECONTROL_H

/*
* coursestoragecontrol.h
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
* - handles the courses aspect of the storage system
* - This is a singleton class
*
* Traceability: CT-028
*
* Acknowledgements: None
*/

#include <QObject>
#include <QSharedPointer>
#include "mainstoragecontrol.h"

class CourseStorageControl : public QObject
{
    Q_OBJECT

public:
    /* Static Member Function: getCourseStorageControl
     * out: Instance of CourseStorageControl, or nothing, if
     *        the CourseStorageControl instance failed to initialize.
     * Side Effects: None
     * Return Value: True, if the CourseStorageControl object
     *   is properly initialized.
     */
    static bool getCourseStorageControl(QSharedPointer<CourseStorageControl>& ptr);

protected:
    /* Constructor
     *   Essentially does nothing
     * Side Effects: None
     */
    CourseStorageControl(void);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

private:
    QSharedPointer<MainStorageControl> mainStorage;

private:
    // Singleton instance
    static QSharedPointer<CourseStorageControl> courseStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // COURSESTORAGECONTROL_H
