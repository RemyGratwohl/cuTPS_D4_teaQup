#ifndef CONTENTVIEWCONTROL_H
#define CONTENTVIEWCONTROL_H

/*
* contentviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentViewControl class:
* - Manages the ContentView subsystem
*
* Traceability: CT-040
*
* Acknowledgements: None
*/

#include <QObject>
#include "contentview.h"
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"
#include "../../server/ContentManagement/book.h"
#include "../../server/ContentManagement/chapter.h"
#include "../../server/ContentManagement/chaptersection.h"
#include "../../server/CourseManagement/course.h"
#include "../../server/CourseManagement/term.h"

class ViewControl;

class ContentViewControl : public QObject
{
    Q_OBJECT
public:
    explicit ContentViewControl(ViewControl *viewController = 0, QObject *parent = 0);

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
    /* Member Function: receiveBookList
     *   Processes the list of Books for the courses in which the STUDENT
     *     user is enrolled.
     * in: Books for the courses in which the student is enrolled,
     *      and their corresponding courses
     *      (Passed in null, and remains null if the operation fails.).
     *
     *      Format:
     *      {term0
     *       course0 in term0, books corresponding to course0,
     *       course1 in term0, books corresponding to course1,
     *       etc.
     *       term1
     *       etc.
     *      }
     *
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool receiveBookList(QVector<SerializableQObject*>* items);

    /* Member Function: receiveBookDetails
     *   Processes a single Book and all of its associated chapters
     *     and chapter sections.
     * in: Book for which to details were retrieved
     * in: Book information, including sub-items, ordered as follows
     *      {
     *       chapter0, chapter sections corresponding to chapter0,
     *       chapter1, chapter sections corresponding to chapter1,
     *       etc.
     *      }
     *
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool receiveBookDetails(Book* book, QVector<SerializableQObject*>* items);

    /* Member Function: receiveBooks
     *   Processes all Books in the system.
     * in: All Books
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool receiveBooks(QVector<SerializableQObject*>* items);

    // Functions to be called to send requests to the server
    // -----------------------------------------------------
    /* All input arguments will be deallocated by these functions
     */
public:

    /* Member Function: addBook
     * in: Book to be added to the system
     * in: Course to be added to the system, if the Book is for a new course
     * in: Term to be added to the system, if the Book is for a new course
     *       and the course is for a new term.
     * Side Effects: None
     * Return Value: None
     */
    void addBook(Book* book, Course* course, Term* term);

    /* Member Function: addChapter
     * in: Chapter to be added to the system
     * Side Effects: None
     * Return Value: None
     */
    void addChapter(Chapter* chapter);

    /* Member Function: addSection
     * in: Chapter section to be added to the system
     * Side Effects: None
     * Return Value: None
     */
    void addSection(ChapterSection* section);

    /* Member Function: updateBook
     * in: Book whose information is to be altered
     * in: Course to be added to the system, if the Book now refers to a new course
     * in: Term to be added to the system, if the Book now refers to a new course
     *       and the course is for a new term.
     * Side Effects: None
     * Return Value: None
     */
    void updateBook(Book* book, Course* course, Term* term);

    /* Member Function: updateChapter
     * in: Chapter whose information is to be altered
     * Side Effects: None
     * Return Value: None
     */
    void updateChapter(Chapter* chapter);

    /* Member Function: updateSection
     * in: Chapter section whose information is to be altered
     * Side Effects: None
     * Return Value: None
     */
    void updateSection(ChapterSection* section);

    /* Member Function: removeBook
     * in: Book to be removed from the system
     * Side Effects: None
     * Return Value: None
     */
    void removeBook(Book* book);

    /* Member Function: removeChapter
     * in: Chapter to be removed from the system
     * Side Effects: None
     * Return Value: None
     */
    void removeChapter(Chapter* chapter);

    /* Member Function: removeSection
     * in: Chapter section to be removed from the system
     * Side Effects: None
     * Return Value: None
     */
    void removeSection(ChapterSection* section);

    /* Member Function: requestBookList
     *   Requests the list of Books for the courses in which the STUDENT
     *     user is enrolled.
     * Side Effects: None
     * Return Value: None
     */
    void requestBookList(void);

    /* Member Function: requestBookDetails
     *   Requests a single Book and all of its associated chapters
     *     and chapter sections.
     * in: Book for which to retrieve details
     * Side Effects: None
     * Return Value: None
     */
    void requestBookDetails(const Book* book);

    /* Member Function: requestBooks
     *   Requests all Books in the system. (For CONTENTMGR users.)
     * Side Effects: None
     * Return Value: None
     */
    void requestBooks(void);

signals:

public slots:

private:
    ViewControl      *viewController;
    ContentView      *contentView;
};

#endif // CONTENTVIEWCONTROL_H

