#include "chaptersection.h"

ChapterSection::ChapterSection() :
    ContentItem(),
    chapterID(0),
    number(0),
    isbn()
{
}

ChapterSection::ChapterSection(
        quint16 id, QString title, quint16 courseID,
        PurchasingDetails *pd, quint16 cID,
        quint16 sn, QString is) :
    ContentItem(id, title, courseID, pd),
    chapterID(cID),
    number(sn),
    isbn(is)
{
}

void ChapterSection::insertToDataStream(QDataStream& ds) const {
    ContentItem::insertToDataStream(ds, CHAPTERSECTION);
}
