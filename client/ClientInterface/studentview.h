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

private slots:
    void on_shoppingCartButton_clicked();
    void on_addToCartButton_clicked();
    void on_viewDetailsButton_clicked();

    void on_DT_BackButton_clicked();

    void on_CSL_BackButton_clicked();

private:
    enum PAGE { LIST = 0, DETAILS, CL, CSL };
    Ui::StudentView *ui;
    ViewControl *controller;
    ContentItemTable *contentItemTable;
};

#endif // STUDENTVIEW_H
