#ifndef COURSEVIEWCONTROL_H
#define COURSEVIEWCONTROL_H

/*
* courseviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* CourseViewControl class:
* - Manages the CourseView subsystem.
*
* Traceability: CT-027
*
* Acknowledgements: None
*/

#include <QObject>
#include "coursemanagementview.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"
#include "../../server/CourseManagement/course.h"
#include "../../server/CourseManagement/term.h"

class ViewControl;

class CourseViewControl : public QObject
{
    Q_OBJECT
public:
    explicit CourseViewControl(ViewControl *viewController = 0, QObject *parent = 0);

    /* Member Function: processMsg
     * Handles a message received from the dispatcher.
     * in: Message to be processed
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
   virtual bool processMsg(Message* msg);

    QWidget* getView();

    // Functions that will be called upon reception of non-error information from the server
    // -------------------------------------------------------------------------------------
    /* All input arguments will be deallocated by these functions
     */
protected:

    /* Member Function: receiveCourses
     *   Processes the courses offered in the given term
     * in: Term corresponding to the courses
     * in: Courses referring to the Term.
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool receiveCourses(Term* term, QVector<SerializableQObject*>* courses);

    /* Member Function: receiveTerms
     *   Processes all terms
     * in: List of all Terms
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool receiveTerms(QVector<SerializableQObject*>* terms);

    // Functions to be called to send requests to the server
    // -----------------------------------------------------
    /* All input arguments will be deallocated by these functions
     */
public:
    /* Member Function: addCourse
     * in: Course to be added to the system
     * in: Term to be added to the system, if the new
     *       course is for a new term.
     * Side Effects: None
     * Return Value: None
     */
    void addCourse(Course* course, Term* term);

    /* Member Function: updateCourse
     * in: Course whose information is to be altered
     * in: Term to be added to the system, if the course
     *       now refers to a new term.
     * Side Effects: If the course referred to a different term,
     *   and it was the only course referring to that term,
     *   the term is deleted on the server.
     * Return Value: None
     */
    void updateCourse(Course* course, Term* term);

    /* Member Function: removeCourse
     * in: Course to be removed from the system
     * Side Effects: If the course was the only course referring
     *   to a particular term, the term is deleted on the server.
     * Return Value: True, if the operation succeeded.
     */
    void removeCourse(Course* course);

    /* Member Function: requestCourses
     *   Requets the courses offered in the given term
     * in: Term for which to retrieve the courses
     * Side Effects: None
     * Return Value: None
     */
    void requestCourses(Term* term);

    /* Member Function: requestTerms
     *   Requests all terms
     * Side Effects: None
     * Return Value: None
     */
    void requestTerms(void);

signals:

public slots:

private:
    ViewControl          *viewController;
    CourseManagementView *courseView;
};

#endif // COURSEVIEWCONTROL_H

