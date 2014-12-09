#include "itemtable.h"
#include "../server/ContentManagement/contentitem.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"
#include <QHeaderView>

ItemTable::ItemTable(QObject *parent, QTableWidget* table) :
    QObject(parent), contentTable(table)
{
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

ItemTable::~ItemTable() {}

bool ItemTable::initialize()
{
    contentTable->setColumnCount(4);
    QTableWidgetItem* selectionColumn = new QTableWidgetItem();
    QTableWidgetItem* titleColumn = new QTableWidgetItem("Title");
    QTableWidgetItem* typeColumn = new QTableWidgetItem("Content Type");
    QTableWidgetItem* idColumn = new QTableWidgetItem("Course ID");
    contentTable->setHorizontalHeaderItem(0, selectionColumn);
    contentTable->setHorizontalHeaderItem(1, titleColumn);
    contentTable->setHorizontalHeaderItem(2, typeColumn);
    contentTable->setHorizontalHeaderItem(3, idColumn);
    contentTable->setSortingEnabled(true);
    contentTable->horizontalHeader()->setStretchLastSection(true);

    // make the title's clickable
    connect(contentTable, SIGNAL(cellClicked(int,int)), this, SLOT(itemClicked(int,int)));
    return true;
}

bool ItemTable::updateTableView(QVector<ContentItem*>* contentList)
{
    int listSize = contentList->size();
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

    return true;
}

void ItemTable::itemClicked(int row, int col)
{
    /*
    if(col == 0) {
        for(int i = 0; i < allItems->size(); ++i) {
            ContentItem* content = allItems->at(i);
            QString text = contentTable->item(row, col)->text();
            if(content->getTitle().compare(text) == 0) {
                contentTable->item(row, 0)->setBackgroundColor(QColor(200, 200, 200));
                contentTable->item(row, 1)->setBackgroundColor(QColor(200, 200, 200));
                contentTable->item(row, 2)->setBackgroundColor(QColor(200, 200, 200));
            }
        }
    }*/
}
