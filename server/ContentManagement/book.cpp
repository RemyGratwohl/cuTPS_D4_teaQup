#include "book.h"

Book::Book() :
    identifier(0),
    contentID(0),
    subtitle(),
    authors(),
    isbn(),
    website(),
    year(0),
    publisher(),
    citation(),
    imageLink()
{}

Book::Book(quint16 id, quint16 cID, QString st, QString a,
     QString is, QString w, quint16 y,
     QString p, QString c, QString il) :
    identifier(id),
    contentID(cID),
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
    SerializableQObject::insertToDataStream(ds, BOOK);
}
