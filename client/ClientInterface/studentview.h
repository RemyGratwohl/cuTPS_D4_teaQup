#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <QWidget>
#include "contentitemtable.h"
#include "../server/ContentManagement/contentitem.h"
#include "../server/UserManagement/user.h"

class ViewControl;

namespace Ui {
class StudentView;
}

class StudentView : public QWidget
{
    Q_OBJECT

public:
    explicit StudentView(ViewControl *controller = 0, User *user = 0);
    ~StudentView();

    bool viewContentItems(QVector<ContentItem *> *contentItems);
    bool refreshView();

private slots:
    void on_shoppingCartButton_clicked();
    void on_addToCartButton_clicked();

private:
    Ui::StudentView *ui;
    ViewControl *controller;
    ContentItemTable *contentItemTable;
};

#endif // STUDENTVIEW_H
