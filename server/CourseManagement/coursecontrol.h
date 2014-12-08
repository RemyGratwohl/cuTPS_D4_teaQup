#ifndef COURSECONTROL_H
#define COURSECONTROL_H

/*
* coursecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* CourseControl class:
* - handles all course operations
*
* Traceability: CT-026
*
* Acknowledgements: None
*/

#include "../util/abstractmanager.h"
#include "../Storage/coursestoragecontrol.h"
#include "course.h"
#include "term.h"

class CourseControl : public AbstractManager
{
    Q_OBJECT
public:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * Side Effects: None
     * All input pointers are treated as shared pointers.
     */
    CourseControl(ServerDispatcher *dispatcher);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

    /* Member Function: processMsg
     *   Handles a message received from the dispatcher,
     *     possibly resulting in messages sent back through the dispatcher
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    virtual bool processMsg(const Message* msg);

    /* Member Function: getCourses
     *   Retrieves the courses with the given ID numbers
     * in: ID numbers of courses
     * out: Course information (ordered to match the input ID numbers)
     *      (Passed in null, and remains null if the operation fails.)
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getCourses(QList<OBJ_ID_TYPE>& courseIDs, QVector<Course*>*& courses, QString& errorMsg);

    /* Member Function: getTerms
     *   Retrieves the terms with the given ID numbers
     * in: ID numbers of terms
     * out: Term information (ordered to match the input ID numbers)
     *      (Passed in null, and remains null if the operation fails.)
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getTerms(QList<OBJ_ID_TYPE>& termIDs, QVector<Term*>*& terms, QString& errorMsg);

    // Helper functions used by processMsg()
private:
    /* Member Function: addCourse
     * in: Course to be added to the system
     * in: Term to be added to the system, if the new
     *       course is for a new term.
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool addCourse(Course* course, Term* term, QString& errorMsg);

    /* Member Function: updateCourse
     * in: Course whose information is to be altered
     * in: Term to be added to the system, if the course
     *       now refers to a new term.
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: If the course referred to a different term,
     *   and it was the only course referring to that term,
     *   the term is deleted.
     * Return Value: True, if the operation succeeded.
     */
    bool updateCourse(Course* course, Term* term, QString& errorMsg);

    /* Member Function: removeCourse
     * in: Course to be removed from the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: If the course was the only course referring
     *   to a particular term, the term is deleted.
     * Return Value: True, if the operation succeeded.
     */
    bool removeCourse(Course* course, QString& errorMsg);

    /* Member Function: getCourses
     *   Retrieves the courses offered in the given term
     * in: Term for which to retrieve the courses
     * out: Courses referring to the input Term,
     *      With the Term itself placed at the start of the list.
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getCourses(Term* term, QVector<SerializableQObject*>*& courses, QString& errorMsg);

    /* Member Function: getTerms
     *   Retrieves all terms
     * out: List of all Terms
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getTerms(QVector<SerializableQObject*>*& terms, QString& errorMsg);

private:
    QSharedPointer<CourseStorageControl> courseStorageControl;
};

#endif // COURSECONTROL_H
