#ifndef ITEMTABLE_H
#define ITEMTABLE_H

#include <QObject>
#include <QTableWidgetItem>
#include <QVector>

class ItemTable : public QObject
{
    Q_OBJECT
public:
    explicit ContentItemTable(QObject *parent = 0);

    virtual ~ContentItemTable();

    /* Member Function: updateTableView
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    virtual bool updateTableView(QVector<SerializableQObject *>* contentList) = 0;

signals:

public slots:
    virtual void itemTitleClicked(int row, int col);

};

#endif // ITEMTABLE_H
