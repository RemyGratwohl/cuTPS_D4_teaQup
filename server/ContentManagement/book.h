#ifndef BOOK_H
#define BOOK_H

/*
* book.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* Book class:
* - contains all data pertaining to the book content items
* - contains publication details as well
*
* Traceability: ET-002
*
* Acknowledgements: None
*/

#include "contentitem.h"

class Book : public ContentItem
{
    Q_OBJECT
    Q_PROPERTY(quint16 id READ getID WRITE setID)
    Q_PROPERTY(quint16 contentID READ getContentID WRITE setContentID)
    Q_PROPERTY(QString subTitle READ getSubTitle WRITE setSubTitle)
    Q_PROPERTY(QString authors READ getAuthors WRITE setAuthors)
    Q_PROPERTY(QString isbn READ getISBN WRITE setISBN)
    Q_PROPERTY(QString website READ getWebsite WRITE setWebsite)
    Q_PROPERTY(quint16 yearPublished READ getYearPublished WRITE setYearPublished)
    Q_PROPERTY(QString publisher READ getPublisher WRITE setPublisher)
    Q_PROPERTY(QString citation READ getCitation WRITE setCitation)
    Q_PROPERTY(QString imageLink READ getImageLink WRITE setImageLink)

public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    Book();

    /* Constructor
     * in: Book ID
     * in: ContentItem ID
     * in: Subtitle
     * in: Authors
     * in: ISBN
     * in: Website
     * in: Year of publication
     * in: Publisher name
     * in: Citation which can be used to reference the book
     *       in a works cited list
     * in: Image link (path to cover page image)
     * Side Effects: None
     */
    Book(quint16 id, quint16 contentID, QString subTitle, QString authors,
         QString isbn, QString website, quint16 yearPublished,
         QString publisher, QString citation, QString imageLink);

    quint16 getID()   const { return identifier;   }
    void setID(quint16 id)   { identifier = id; }

    quint16 getContentID()   const { return contentID;   }
    void setContentID(quint16 id)   { contentID = id; }

    QString getSubTitle() const { return subtitle; }
    void setSubTitle(const QString& t) { subtitle = t; }

    QString getAuthors() const { return authors; }
    void setAuthors(const QString& a) { authors = a; }

    QString getISBN() const { return isbn; }
    void setISBN(const QString& i) { isbn = i; }

    QString getWebsite() const { return website; }
    void setWebsite(const QString& w) { website = w; }

    quint16 getYearPublished()   const { return year;   }
    void setYearPublished(quint16 y)   { year = y; }

    QString getPublisher() const { return publisher; }
    void setPublisher(const QString& p) { publisher = p; }

    QString getCitation() const { return citation; }
    void setCitation(const QString& c) { citation = c; }

    QString getImageLink() const { return imageLink; }
    void setImageLink(const QString& il) { imageLink = il; }

    /* Member Function: insertToDataStream
     *   Serialization function, which inserts the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

private:
    quint16 identifier;
    quint16 contentID;
    QString subtitle;
    QString authors;
    QString isbn;
    QString website;
    quint16 year;
    QString publisher;
    QString citation;
    QString imageLink;
};

#endif // BOOK_H
