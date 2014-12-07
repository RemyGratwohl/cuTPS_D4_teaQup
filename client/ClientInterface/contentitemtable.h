#ifndef CONTENTITEMTABLE_H
#define CONTENTITEMTABLE_H

#include <QObject>
#include "itemtable.h"

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

signals:

public slots:
    virtual void itemTitleClicked(int row, int col);

private:
    QVector<ContentItem*>* allItems;
    QVector<ContentItem*>* selectedItems;

};

#endif // CONTENTITEMTABLE_H
