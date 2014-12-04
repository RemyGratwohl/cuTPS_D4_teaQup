#include "chapter.h"

Chapter::Chapter() :
    ContentItem(),
    bookID(0),
    number(0),
    isbn()
{
}

Chapter::Chapter(OBJ_ID_TYPE id, QString title, OBJ_ID_TYPE courseID,
                 PurchasingDetails *pd, OBJ_ID_TYPE bID,
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
