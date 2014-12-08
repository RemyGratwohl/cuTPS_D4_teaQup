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
    allItems = contentList;
    for(int i = 0; i < listSize; ++i) {
        ContentItem* content = contentList->at(i);

        QTableWidgetItem* selectionButton = new QTableWidgetItem("");
        selectionButton->setCheckState(Qt::Unchecked);
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

        itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsSelectable);
        itemType->setFlags(itemType->flags() ^ Qt::ItemIsSelectable);
        itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsSelectable);

        // add the text items to the table
        contentTable->setRowCount(listSize);
        contentTable->setItem(i, 0, selectionButton);
        contentTable->setItem(i, 1, itemTitle);
        contentTable->setItem(i, 2, itemType);
        contentTable->setItem(i, 3, itemCourseID);

        // adjust column width to fit all contents
        contentTable->resizeColumnsToContents();
        contentTable->horizontalHeader()->setStretchLastSection(true);
    }

    //refreshTableView();

    return true;
}

bool ContentItemTable::addSelectedItems()
{
    selectedItems->empty();
    for(int i = 0; i < contentTable->rowCount(); ++i) {
        if(contentTable->item(i, 0)->checkState() == Qt::Checked) {
            QString text = contentTable->item(i, 1)->text();
            for(int i = 0; i < allItems->size(); ++i) {
                ContentItem* content = allItems->at(i);
                if(content->getTitle().compare(text) == 0) {
                    selectedItems->push_back(allItems->at(i));
                }
            }
        }
        contentTable->item(i, 0)->setCheckState(Qt::Unchecked);
    }
    return true;
}

void ContentItemTable::itemClicked(int row, int col)
{
    if(col == 0) {
        for(int i = 0; i < allItems->size(); ++i) {
            ContentItem* content = allItems->at(i);
            QString text = contentTable->item(row, 1)->text();
            if(content->getTitle().compare(text) == 0) {
                selectedItems->push_back(allItems->at(i));
                //contentTable->item(row, 0)->setBackgroundColor(QColor(200, 200, 200));
                //contentTable->item(row, 1)->setBackgroundColor(QColor(200, 200, 200));
                //contentTable->item(row, 2)->setBackgroundColor(QColor(200, 200, 200));
            }
        }
    }
}

QVector<ContentItem *>* ContentItemTable::getSelectedItems() const
{
    return selectedItems;
}
