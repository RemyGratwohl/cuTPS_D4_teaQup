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
#include <QVector>
#include <QDebug>
#include "mainstoragecontrol.h"
#include "../ContentManagement/book.h"
#include "../ContentManagement/chapter.h"
#include "../ContentManagement/chaptersection.h"
#include "../CourseManagement/course.h"
#include "../CourseManagement/term.h"

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

    // Public interface needed by the ContentManagement subsystem
public:
    /* Member Function: addBook
    * in: Book to be added to the system
    * in: Course to be added to the system, if the Book is for a new course
    *       (otherwise null)
    * in: Term to be added to the system, if the Book is for a new course
    *       and the course is for a new term.
    *       (otherwise null)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool addBook(Book* book, Course* course, Term* term, QString& errorMsg);

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
    * in: Course to be added to the system, if the Book now refers to a new course
    *       (otherwise null)
    * in: Term to be added to the system, if the Book now refers to a new course
    *       and the course is for a new term.
    *       (otherwise null)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool updateBook(Book* book, Course* course, Term* term, QString& errorMsg);

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

    /* Member Function: getBook
    * Returns a single book
    * in: ID of the Book to retrieve
    * out: Book retrieved
    *      (Passed in null, and remains null if the operation fails.)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getBook(OBJ_ID_TYPE bookID, Book* book, QString& errorMsg);

    /* Member Function: getBookList
    * Retrieves the list of Books for the courses in which the student
    * user is enrolled.
    * in: User whose books are to be retrieved. (Must be a student user.)
    * out: Books for the courses in which the student is enrolled
    *      (Passed in null, and remains null if the operation fails.)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getBookList(User* student, QVector<Book*>*& items, QString& errorMsg);

    /* Member Function: getChapters
    * Retrieves a all of the associated chapters of a book
    * in: Book for which chapters are to be retrieved
    * out: Chapters corresponding to the book
    *      (Passed in null, and remains null if the operation fails.)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getChapters(Book* book, QVector<Chapter*>*& items, QString& errorMsg);

    /* Member Function: getSections
    * Retrieves a all of the associated chapter sections of a chapter
    * in: Chapter for which chapter sections are to be retrieved
    * out: Chapter sections corresponding to the chapter
    *      (Passed in null, and remains null if the operation fails.)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getSections(Chapter* chapter, QVector<ChapterSection*>*& items, QString& errorMsg);

    /* Member Function: getBooks
    * Retrieves all Books in the system.
    * out: All Books
    *      (Passed in null, and remains null if the operation fails.)
    * out: QString to be altered in the event of an error to hold an error message
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getBooks(QVector<Book*>*& items, QString& errorMsg);

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

    bool isTerm(Term* term, QString& id);
    bool isCourse(Course* course, QString& id);
    bool isContentItem(QString& ISBN);


private:
    // Singleton instance
    static QSharedPointer<ContentStorageControl> contentStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // CONTENTSTORAGECONTROL_H
