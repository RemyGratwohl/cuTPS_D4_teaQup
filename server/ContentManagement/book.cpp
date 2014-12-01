#include "book.h"

Book::Book() :
    ContentItem(),
    subtitle(),
    authors(),
    isbn(),
    website(),
    year(0),
    publisher(),
    citation(),
    imageLink()
{}

Book::Book(quint16 id, QString title, quint16 courseID,
           PurchasingDetails *pd, QString st, QString a,
           QString is, QString w, quint16 y,
           QString p, QString c, QString il) :
    ContentItem(id, title, courseID, pd),
    subtitle(st),
    authors(a),
    isbn(is),
    website(w),
    year(y),
    publisher(p),
    citation(c),
    imageLink(il)
{}

void Book::insertToDataStream(QDataStream& ds) const {
    ContentItem::insertToDataStream(ds, BOOK);
}
