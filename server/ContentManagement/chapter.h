#ifndef CHAPTER_H
#define CHAPTER_H

/*
* chapter.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Chapter class:
* - contains all data pertaining to the chapter content items
* - is a distinct chapter of a book content item
*
* Traceability: ET-003
*
* Acknowledgements: None
*/

#include "contentitem.h"

class Chapter : public ContentItem
{
    Q_OBJECT
    Q_PROPERTY(quint16 bookID READ getBookID WRITE setBookID)
    Q_PROPERTY(quint16 chapterNumber READ getChapterNumber WRITE setChapterNumber)
    Q_PROPERTY(QString isbn READ getISBN WRITE setISBN)
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    Chapter();

    /* Constructor
     * in: Chapter ID (content item ID)
     * in: Title
     * in: Corresponding course ID
     * in: Purchasing details (null if not for sale)
     * in: Corresponding book ID
     * in: Chapter number
     * in: ISBN
     * Side Effects: None
     */
    Chapter(quint16 chapterID, QString title, quint16 courseID,
            PurchasingDetails *purchaseDetails, quint16 bookID,
            quint16 chapterNumber, QString isbn);

    quint16 getBookID()   const { return bookID;   }
    void setBookID(quint16 id)   { bookID = id; }

    quint16 getChapterNumber()   const { return number;   }
    void setChapterNumber(quint16 n)   { number = n; }

    QString getISBN() const { return isbn; }
    void setISBN(const QString& i) { isbn = i; }

    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

private:
    quint16 bookID;
    quint16 number;
    QString isbn;
};

#endif // CHAPTER_H
