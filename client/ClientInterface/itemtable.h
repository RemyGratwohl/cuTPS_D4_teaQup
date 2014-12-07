#ifndef ITEMTABLE_H
#define ITEMTABLE_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVector>
#include "../server/ContentManagement/contentitem.h"

class ItemTable : public QObject
{
    Q_OBJECT
public:
    ItemTable(QObject *parent = 0, QTableWidget* table = 0);
    ~ItemTable();

    /* Member Function: updateTableView
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    virtual bool updateTableView(QVector<ContentItem*>* contentList);

    virtual bool initialize();

signals:

public slots:
    virtual void itemTitleClicked(int row, int col) = 0;

protected:
    QTableWidget *contentTable;

};

#endif // ITEMTABLE_H
