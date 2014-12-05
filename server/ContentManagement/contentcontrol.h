#ifndef CONTENTCONTROL_H
#define CONTENTCONTROL_H

/*
* contentcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentControl class:
* - handles all operations on content items in the server
*
* Traceability: CT-039
*
* Acknowledgements: None
*/

#include "../util/abstractmanager.h"
#include "../CourseManagement/coursecontrol.h"
#include "../Storage/contentstoragecontrol.h"
#include "book.h"
#include "chapter.h"
#include "chaptersection.h"

class ContentControl : public AbstractManager
{
    Q_OBJECT
public:
    /* Constructor
     * in: Dispatcher to use for sending messages to the client
     *       (Also the parent of this object.)
     * in: Course management subsystem control object,
     *       used when content operations involve course management.
     * Side Effects: None
     * All input pointers are treated as shared pointers.
     */
    ContentControl(ServerDispatcher *dispatcher,
                   CourseControl *courseControl);

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

    // Helper functions used by processMsg()
private:
    /* Member Function: addBook
     * in: Book to be added to the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool addBook(Book* book, QString& errorMsg);

    /* Member Function: addChapter
     * in: Chapter to be added to the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool addChapter(Chapter* chapter, QString& errorMsg);

    /* Member Function: addSection
     * in: Chapter section to be added to the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool addSection(ChapterSection* section, QString& errorMsg);

    /* Member Function: updateBook
     * in: Book whose information is to be altered
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool updateBook(Book* book, QString& errorMsg);

    /* Member Function: updateChapter
     * in: Chapter whose information is to be altered
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool updateChapter(Chapter* chapter, QString& errorMsg);

    /* Member Function: updateSection
     * in: Chapter section whose information is to be altered
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool updateSection(ChapterSection* section, QString& errorMsg);

    /* Member Function: removeBook
     * in: Book to be removed from the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool removeBook(Book* book, QString& errorMsg);

    /* Member Function: removeChapter
     * in: Chapter to be removed from the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool removeChapter(Chapter* chapter, QString& errorMsg);

    /* Member Function: removeSection
     * in: Chapter section to be removed from the system
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool removeSection(ChapterSection* section, QString& errorMsg);

    /* Member Function: getBookList
     *   Retrieves the list of Books for the courses in which the student
     *     user is enrolled.
     * in: User whose books are to be retrieved. (Must be a student user.)
     * out: Books for the courses in which the student is enrolled
     *      (passed in null)
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getBookList(User* student, QVector<SerializableQObject*>*& items, QString& errorMsg);

    /* Member Function: getBookDetails
     *   Retrieves a single Book and all of its associated chapters
     *     and chapter sections.
     * in: Book for which to retrieve details
     * out: Book information, including sub-items, ordered as follows
     *      {book,
     *       chapter0, chapter sections corresponding to chapter0,
     *       chapter1, chapter sections corresponding to chapter1,
     *       etc.
     *      }
     *     (passed in null)
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getBookDetails(const Book* book, QVector<SerializableQObject*>*& items, QString& errorMsg);

    /* Member Function: getBooks
     *   Retrieves all Books in the system.
     * out: All Books
     *     (passed in null)
     * out: QString to be altered in the event of an error to hold an error message
     * Side Effects: None
     * Return Value: True, if the operation succeeded.
     */
    bool getBooks(QVector<SerializableQObject*>*& items, QString& errorMsg);

private:
    CourseControl *courseControl;
    QSharedPointer<ContentStorageControl> contentStorageControl;
};

#endif // CONTENTCONTROL_H
