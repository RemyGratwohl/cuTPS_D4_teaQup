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
    Q_PROPERTY(OBJ_ID_TYPE chapterID READ getChapterID WRITE setChapterID)
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
     * Side Effects: Purchasing details is adopted
     *   as a child of this object.
     */
    ChapterSection(OBJ_ID_TYPE chapterSectionID, QString title, OBJ_ID_TYPE courseID,
                   PurchasingDetails *purchaseDetails,
                   OBJ_ID_TYPE chapterID,
                   quint16 sectionNumber, QString isbn);

    OBJ_ID_TYPE getChapterID()   const { return chapterID;   }
    void setChapterID(OBJ_ID_TYPE id)   { chapterID = id; }

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
    OBJ_ID_TYPE chapterID;
    quint16 number;
    QString isbn;
};

#endif // CHAPTERSECTION_H
