#include "shoppingcarttable.h"
#include "../server/ContentManagement/contentitem.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

ShoppingCartTable::ShoppingCartTable(QObject *parent, QTableWidget *table) :
    ItemTable(parent, table)
{
    shoppingItems = new QVector<ContentItem*>();
}

ShoppingCartTable::~ShoppingCartTable() {}

bool ShoppingCartTable::updateTableView(QVector<ContentItem*>* contentList)
{
    int listSize = contentList->size();
    shoppingItems = contentList;

    if(listSize == 0) {
        // add the text items to the table
        contentTable->setRowCount(listSize);
        return true;
    }

    for(int i = 0; i < listSize; ++i) {
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
        contentTable->horizontalHeader()->setStretchLastSection(true);
    }
    return true;
}

void ShoppingCartTable::itemClicked(int row, int col)
{
    if(col == 0) {
        QString text = contentTable->item(row, col)->text();
        for(int i = 0; i < shoppingItems->size(); ++i) {
            ContentItem* content = shoppingItems->at(i);
            if(content->getTitle().compare(text) == 0) {
                shoppingItems->remove(i);
            }
        }
    }
    updateTableView(shoppingItems);
}
