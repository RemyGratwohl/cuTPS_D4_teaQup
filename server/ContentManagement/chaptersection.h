#ifndef CHAPTERSECTION_H
#define CHAPTERSECTION_H

/*
* chaptersection.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ChapterSection class:
* - contains all data pertaining to the chaptersection content items
* - is a section of a chapter content item
*
* Traceability: ET-004
*
* Acknowledgements: None
*/

#include "contentitem.h"

class ChapterSection : public ContentItem
{
    Q_OBJECT
    Q_PROPERTY(quint16 chapterID READ getChapterID WRITE setChapterID)
    Q_PROPERTY(quint16 sectionNumber READ getSectionNumber WRITE setSectionNumber)
    Q_PROPERTY(QString isbn READ getISBN WRITE setISBN)
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    ChapterSection();

    /* Constructor
     * in: Chapter section ID (content item ID)
     * in: Title
     * in: Corresponding course ID
     * in: Purchasing details (null if not for sale)
     * in: Corresponding chapter ID
     * in: Section number
     * in: ISBN
     * Side Effects: None
     */
    ChapterSection(quint16 chapterSectionID, QString title, quint16 courseID,
                   PurchasingDetails *purchaseDetails,
                   quint16 chapterID,
                   quint16 sectionNumber, QString isbn);

    quint16 getChapterID()   const { return chapterID;   }
    void setChapterID(quint16 id)   { chapterID = id; }

    quint16 getSectionNumber()   const { return number;   }
    void setSectionNumber(quint16 n)   { number = n; }

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
    quint16 chapterID;
    quint16 number;
    QString isbn;
};

#endif // CHAPTERSECTION_H
