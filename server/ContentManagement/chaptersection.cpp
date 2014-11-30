#include "chaptersection.h"

ChapterSection::ChapterSection() :
    identifier(0),
    chapterID(0),
    number(0),
    isbn()
{
}

ChapterSection::ChapterSection(
        quint16 id, quint16 cID,
        quint16 sn, QString is) :
    identifier(id),
    chapterID(cID),
    number(sn),
    isbn(is)
{
}

void ChapterSection::insertToDataStream(QDataStream& ds) const {
    ContentItem::insertToDataStream(ds, CHAPTERSECTION);
}
