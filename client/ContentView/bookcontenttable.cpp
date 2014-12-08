#include "bookcontenttable.h"
#include "../server/ContentManagement/contentitem.h"
#include "../server/ContentManagement/book.h"
#include "../server/ContentManagement/chapter.h"
#include "../server/ContentManagement/chaptersection.h"

BookContentTable::BookContentTable(QObject *parent, QTableWidget *table)
    : ItemTable(parent, table)
{
}

BookContentTable::~BookContentTable() {}

bool BookContentTable::initialize(QPushButton *button)
{
    editBookButton = button;
    handleEditButton();

    contentTable->setColumnCount(3);
    QTableWidgetItem* titleColumn = new QTableWidgetItem("Title");
    QTableWidgetItem* typeColumn = new QTableWidgetItem("Content Type");
    QTableWidgetItem* idColumn = new QTableWidgetItem("Course ID");
    contentTable->setHorizontalHeaderItem(0, titleColumn);
    contentTable->setHorizontalHeaderItem(1, typeColumn);
    contentTable->setHorizontalHeaderItem(2, idColumn);
    contentTable->setSortingEnabled(true);
    contentTable->horizontalHeader()->setStretchLastSection(true);

    contentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    contentTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    allItems = new QVector<ContentItem*>();

    // make the title's clickable
    connect(contentTable, SIGNAL(cellClicked(int,int)), this, SLOT(itemClicked(int,int)));
    return true;
}

bool BookContentTable::handleEditButton()
{
    if(contentTable->currentIndex().isValid() == false) {
        editBookButton->setDisabled(true);
    } else {
        editBookButton->setDisabled(false);
    }
    return true;
}

bool BookContentTable::isItemSelected()
{
    return contentTable->currentIndex().isValid();
}

bool BookContentTable::updateTableView(QVector<ContentItem*>* contentList)
{
    int listSize = contentList->size();
    allItems = contentList;
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

        //itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsSelectable);
        //itemType->setFlags(itemType->flags() ^ Qt::ItemIsSelectable);
        //itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsSelectable);

        // add the text items to the table
        contentTable->setRowCount(listSize);
        contentTable->setItem(i, 0, itemTitle);
        contentTable->setItem(i, 1, itemType);
        contentTable->setItem(i, 2, itemCourseID);

        // adjust column width to fit all contents
        contentTable->resizeColumnsToContents();
        contentTable->horizontalHeader()->setStretchLastSection(true);
    }

    //refreshTableView();

    return true;
}

void BookContentTable::itemClicked(int row, int col)
{
    handleEditButton();
}
