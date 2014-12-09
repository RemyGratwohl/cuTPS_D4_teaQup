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
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
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
        selectionButton->setFlags(selectionButton->flags() ^ Qt::ItemIsEditable);
        itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsEditable);
        itemType->setFlags(itemType->flags() ^ Qt::ItemIsEditable);
        itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsEditable);

        selectionButton->setFlags(selectionButton->flags() ^ Qt::ItemIsSelectable);
        //itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsSelectable);
        //itemType->setFlags(itemType->flags() ^ Qt::ItemIsSelectable);
        //itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsSelectable);

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

bool ContentItemTable::isItemSelected()
{
    return contentTable->currentIndex().isValid();
}

Book *ContentItemTable::getCurrentBook()
{
    if(isItemSelected()) {
        QModelIndex index = contentTable->currentIndex();
        QTableWidgetItem* item = contentTable->item(index.row(), 1);
        for(int i = 0; i < allItems->size(); ++i) {
            if(item->text().compare(allItems->at(i)->getTitle()) == 0) {
                return qobject_cast<Book*>(allItems->at(i));
            }
        }
    }
    return 0;
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

bool ContentItemTable::initialize(QPushButton* button)
{
    detailsButton = button;
    handleDetailsButton();

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

bool ContentItemTable::handleDetailsButton()
{
    if(contentTable->currentIndex().isValid() == false) {
        detailsButton->setDisabled(true);
    } else {
        detailsButton->setDisabled(false);
    }
    return true;
}

void ContentItemTable::itemClicked(int row, int col)
{
    handleDetailsButton();
}

QVector<ContentItem *>* ContentItemTable::getSelectedItems() const
{
    return selectedItems;
}
