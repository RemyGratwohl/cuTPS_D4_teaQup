#include "chapter.h"

Chapter::Chapter() :
    identifier(0),
    contentID(0),
    bookID(0),
    number(0),
    isbn()
{
}

Chapter::Chapter(quint16 id, quint16 cID, quint16 bID,
                 quint16 cn, QString is) :
    identifier(id),
    contentID(cID),
    bookID(bID),
    number(cn),
    isbn(is)
{
}

void Chapter::insertToDataStream(QDataStream& ds) const {
    ContentItem::insertToDataStream(ds, CHAPTER);
}
