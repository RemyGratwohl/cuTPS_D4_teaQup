#include "chaptersection.h"

ChapterSection::ChapterSection() :
    ContentItem(),
    chapterID(0),
    number(0),
    isbn()
{
}

ChapterSection::ChapterSection(
        OBJ_ID_TYPE id, QString title, OBJ_ID_TYPE courseID,
        PurchasingDetails *pd, OBJ_ID_TYPE cID,
        OBJ_ID_TYPE sn, QString is) :
    ContentItem(id, title, courseID, pd),
    chapterID(cID),
    number(sn),
    isbn(is)
{
}

void ChapterSection::insertToDataStream(QDataStream& ds) const {
    ContentItem::insertToDataStream(ds, CHAPTERSECTION);
}
