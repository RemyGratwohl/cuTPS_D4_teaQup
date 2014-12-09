#ifndef CONTENTITEMTABLE_H
#define CONTENTITEMTABLE_H

#include <QObject>
#include "itemtable.h"
#include "../server/ContentManagement/book.h"
#include <QPushButton>

class ContentItemTable : public ItemTable
{
    Q_OBJECT
public:
    ContentItemTable(QObject *parent = 0, QTableWidget* table = 0);
    ~ContentItemTable();

    /* Member Function: updateTableView
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    virtual bool updateTableView(QVector<ContentItem*>* contentList);

    QVector<ContentItem*>* getSelectedItems() const;

    virtual bool initialize(QPushButton* button);

    bool addSelectedItems();

    bool isItemSelected();

    bool handleDetailsButton();

    Book *getCurrentBook();

signals:

public slots:
    virtual void itemClicked(int row, int col);

private:
    QVector<ContentItem*>* allItems;
    QVector<ContentItem*>* selectedItems;
    QPushButton* detailsButton;
};

#endif // CONTENTITEMTABLE_H
