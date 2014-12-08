#include "coursetable.h"
#include <QHeaderView>

CourseTable::CourseTable(QObject *parent, QTableWidget *table)
    : QObject(parent), contentTable(table)
{
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

CourseTable::~CourseTable() {}

bool CourseTable::initialize(QPushButton* editButton)
{
    editCourseButton = editButton;
    handleEditButton();

    contentTable->setColumnCount(2);
    QTableWidgetItem* titleColumn = new QTableWidgetItem("Title");
    QTableWidgetItem* idColumn = new QTableWidgetItem("Course ID");
    contentTable->setHorizontalHeaderItem(0, titleColumn);
    contentTable->setHorizontalHeaderItem(1, idColumn);
    contentTable->setSortingEnabled(true);
    contentTable->horizontalHeader()->setStretchLastSection(true);

    contentTable->setSelectionMode(QAbstractItemView::SingleSelection);
    contentTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    allItems = new QVector<Course*>();

    // make the title's clickable
    connect(contentTable, SIGNAL(cellClicked(int,int)), this, SLOT(itemClicked(int,int)));
    return true;
}

bool CourseTable::handleEditButton()
{
    if(contentTable->currentIndex().isValid() == false) {
        editCourseButton->setDisabled(true);
    } else {
        editCourseButton->setDisabled(false);
    }
    return true;
}

bool CourseTable::isItemSelected()
{
    return contentTable->currentIndex().isValid();
}

bool CourseTable::updateTableView(QVector<Course*>* contentList)
{
    int listSize = contentList->size();
    allItems = contentList;
    for(int i = 0; i < listSize; ++i) {
        Course* content = contentList->at(i);

        QTableWidgetItem* itemTitle;
        QTableWidgetItem* itemCourseID;

        // set title and course id values
        itemTitle = new QTableWidgetItem(content->getName());
        itemCourseID = new QTableWidgetItem((quint64)content->getID());

        // make the cells uneditable
        itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsEditable);
        itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsEditable);

        //itemTitle->setFlags(itemTitle->flags() ^ Qt::ItemIsSelectable);
        //itemCourseID->setFlags(itemCourseID->flags() ^ Qt::ItemIsSelectable);

        // add the text items to the table
        contentTable->setRowCount(listSize);
        contentTable->setItem(i, 0, itemTitle);
        contentTable->setItem(i, 1, itemCourseID);

        // adjust column width to fit all contents
        contentTable->resizeColumnsToContents();
        contentTable->horizontalHeader()->setStretchLastSection(true);
    }

    //refreshTableView();

    return true;
}

void CourseTable::itemClicked(int row, int col)
{
    handleEditButton();
}
