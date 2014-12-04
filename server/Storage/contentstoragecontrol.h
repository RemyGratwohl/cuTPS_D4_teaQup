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
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool addBook(Book* book);

    /* Member Function: addChapter
    * in: Chapter to be added to the system
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool addChapter(Chapter* chapter);

    /* Member Function: addSection
    * in: Chapter section to be added to the system
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool addSection(ChapterSection* section);

    /* Member Function: updateBook
    * in: Book whose information is to be altered
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool updateBook(Book* book);

    /* Member Function: updateChapter
    * in: Chapter whose information is to be altered
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool updateChapter(Chapter* chapter);

    /* Member Function: updateSection
    * in: Chapter section whose information is to be altered
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool updateSection(ChapterSection* section);

    /* Member Function: removeBook
    * in: Book to be removed from the system
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool removeBook(Book* book);

    /* Member Function: removeChapter
    * in: Chapter to be removed from the system
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool removeChapter(Chapter* chapter);

    /* Member Function: removeSection
    * in: Chapter section to be removed from the system
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool removeSection(ChapterSection* section);

    /* Member Function: getBookList
    * Retrieves the list of Books for the courses in which the student
    * user is enrolled.
    * in: User whose books are to be retrieved. (Must be a student user.)
    * out: Books for the courses in which the student is enrolled
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getBookList(User* student, QVector<Book*>*& items);

    /* Member Function: getChapters
    * Retrieves a all of the associated chapters of a book
    * in: Book for which chapters are to be retrieved
    * out: Chapters corresponding to the book
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getChapters(Book* book, QVector<Chapter*>*& items);

    /* Member Function: getSections
    * Retrieves a all of the associated chapter sections of a chapter
    * in: Chapter for which chapter sections are to be retrieved
    * out: Chapter sections corresponding to the chapter
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getSections(Chapter* chapter, QVector<ChapterSection*>*& items);

    /* Member Function: getBooks
    * Retrieves all Books in the system.
    * out: All Books
    * Side Effects: None
    * Return Value: True, if the operation succeeded.
    */
    bool getBooks(QVector<Book*>*& items);

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
