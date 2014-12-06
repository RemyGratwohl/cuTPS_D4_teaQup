#ifndef CONTENTITEMTABLE_H
#define CONTENTITEMTABLE_H

#include <QObject>
#include "itemtable.h"

class ContentItemTable : public ItemTable
{
    Q_OBJECT
public:
    explicit ContentItemTable(QObject *parent = 0);

    /* Member Function: updateTableView
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    bool updateTableView(QVector<SerializableQObject *>* contentList);

signals:

public slots:
    void itemTitleClicked(int row, int col);

};

#endif // CONTENTITEMTABLE_H
