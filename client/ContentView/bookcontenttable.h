#ifndef BOOKCONTENTTABLE_H
#define BOOKCONTENTTABLE_H

#include "../ClientInterface/itemtable.h"
#include <QPushButton>
#include "../server/ContentManagement/book.h"

class BookContentTable : public ItemTable
{
    Q_OBJECT
public:
    BookContentTable(QObject *parent = 0, QTableWidget* table = 0);
    ~BookContentTable();

    /* Member Function: updateTableView
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    virtual bool updateTableView(QVector<Book *> *contentList);

    virtual bool initialize(QPushButton* button);

    bool isItemSelected();

signals:

public slots:
    virtual void itemClicked(int row, int col);

protected:
    QVector<Book*>* allItems;
    QPushButton* editBookButton;

private:
    bool handleEditButton();
};

#endif // BOOKCONTENTTABLE_H
