#include "chapter.h"

Chapter::Chapter() :
    ContentItem(),
    bookID(0),
    number(0),
    isbn()
{
}

Chapter::Chapter(quint16 id, QString title, quint16 courseID,
                 PurchasingDetails *pd, quint16 bID,
                 quint16 cn, QString is) :
    ContentItem(id, title, courseID, pd),
    bookID(bID),
    number(cn),
    isbn(is)
{
}

void Chapter::insertToDataStream(QDataStream& ds) const {
    ContentItem::insertToDataStream(ds, CHAPTER);
}
