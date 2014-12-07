#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <QWidget>
#include "contentitemtable.h"
#include "../server/ContentManagement/contentitem.h"

class ViewControl;

namespace Ui {
class StudentView;
}

class StudentView : public QWidget
{
    Q_OBJECT

public:
    explicit StudentView(ViewControl *controller = 0);
    ~StudentView();

    bool viewContentItems(QVector<SerializableQObject*>* contentItems);

private slots:
    void on_shoppingCartButton_clicked();

private:
    Ui::StudentView *ui;
    ViewControl *controller;
    ContentItemTable *contentItemTable;
};

#endif // STUDENTVIEW_H
