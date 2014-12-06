#include "itemtable.h"

ContentItemTable::ContentItemTable(QObject *parent) :
    QObject(parent)
{
    ui->contentWidget->setColumnCount(3);
    QTableWidgetItem* firstColumn = new QTableWidgetItem("Title");
    QTableWidgetItem* secondColumn = new QTableWidgetItem("Content Type");
    QTableWidgetItem* thirdColumn = new QTableWidgetItem("Course ID");
    ui->contentWidget->setHorizontalHeaderItem(0, firstColumn);
    ui->contentWidget->setHorizontalHeaderItem(1, secondColumn);
    ui->contentWidget->setHorizontalHeaderItem(2, thirdColumn);
    ui->contentWidget->setSortingEnabled(true);
    ui->contentWidget->horizontalHeader()->setStretchLastSection(true);

    // make the title's clickable
    connect(ui->contentWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemTitleClicked(int,int)));
}

bool ItemTable::updateTableView(QVector<SerializableQObject *>* contentList)
{
    int listSize = contentList->size();
    for(int i = 0; i < listSize; ++i) {
        ContentItem* content = qobject_cast<ContentItem*>(contentList->at(i));

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
        ui->contentWidget->setRowCount(listSize);
        ui->contentWidget->setItem(i, 0, itemTitle);
        ui->contentWidget->setItem(i, 1, itemType);
        ui->contentWidget->setItem(i, 2, itemCourseID);

        // adjust column width to fit all contents
        ui->contentWidget->resizeColumnsToContents();
    }

    return true;
}

void ItemTable::itemTitleClicked(int row, int col)
{
    if(col == 0) {
        for(int i = 0; i < allItems->size(); ++i) {
            ContentItem* content = qobject_cast<ContentItem*>(allItems->at(i));
            QString text = ui->contentWidget->item(row, col)->text();
            if(content->getTitle().compare(text) == 0) {
                selectedItems->push_back(allItems->at(i));
                ui->contentWidget->item(row, 0)->setBackgroundColor(QColor(200, 200, 200));
                ui->contentWidget->item(row, 1)->setBackgroundColor(QColor(200, 200, 200));
                ui->contentWidget->item(row, 2)->setBackgroundColor(QColor(200, 200, 200));
            }
        }
    }
}
