#include "contentitemtable.h"
#include "../server/ContentManagement/contentitem.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

ContentItemTable::ContentItemTable(QObject *parent, QTableWidget *table) :
    ItemTable(parent, table)
{
    allItems = new QVector<ContentItem*>();
    selectedItems = new QVector<ContentItem*>();
}

ContentItemTable::~ContentItemTable() {}

bool ContentItemTable::updateTableView(QVector<ContentItem*>* contentList)
{
    int listSize = contentList->size();
    for(int i = 0; i < listSize; ++i) {
        allItems->push_back(contentList->at(i));
        ContentItem* content = contentList->at(i);

        QTableWidgetItem* itemTitle;
        QTableWidgetItem* itemType;
        QTableWidgetItem* itemCourseID;

        // set title and course id values
        itemTitle = new QTableWidgetItem(content->getTitle());
        itemCourseID = new QTableWidgetItem((quint64)content->getCourseID());

        // determine the type of the content item
        Book* book = 0;
        Chapter* chapter = 0;
        ChapterSection* chapterSection = 0;
        if((book = qobject_cast<Book*>(content)) != 0) {
            itemType = new QTableWidgetItem("Book");
        } else if((chapter = qobject_cast<Chapter*>(content)) != 0) {
            itemType = new QTableWidgetItem("Chapter");
        } else if((chapterSection = qobject_cast<ChapterSection*>(content)) != 0) {
            itemType = new QTableWidgetItem("ChapterSection");
        }

        // make the cells uneditable
        itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsEditable);
        itemType->setFlags(itemType->flags() ^ Qt::ItemIsEditable);
        itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsEditable);

        // add the text items to the table
        contentTable->setRowCount(listSize);
        contentTable->setItem(i, 0, itemTitle);
        contentTable->setItem(i, 1, itemType);
        contentTable->setItem(i, 2, itemCourseID);

        // adjust column width to fit all contents
        contentTable->resizeColumnsToContents();
    }

    return true;
}

void ContentItemTable::itemTitleClicked(int row, int col)
{
    if(col == 0) {
        for(int i = 0; i < allItems->size(); ++i) {
            ContentItem* content = allItems->at(i);
            QString text = contentTable->item(row, col)->text();
            if(content->getTitle().compare(text) == 0) {
                selectedItems->push_back(allItems->at(i));
                contentTable->item(row, 0)->setBackgroundColor(QColor(200, 200, 200));
                contentTable->item(row, 1)->setBackgroundColor(QColor(200, 200, 200));
                contentTable->item(row, 2)->setBackgroundColor(QColor(200, 200, 200));
            }
        }
    }
}

QVector<ContentItem *>* ContentItemTable::getSelectedItems() const
{
    return selectedItems;
}
