#ifndef SHOPPINGCARTVIEW_H
#define SHOPPINGCARTVIEW_H

/*
* shoppingcartview.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ShoppingCartView class:
* - The user interface class which displays the user's shopping cart contents.
*
* Traceability: BD-004
*
* Acknowledgements: None
*/

#include <QWidget>
#include "../server/ServerCommunication/serializableqobject.h"
#include "../Shopping/shoppingcarttable.h"

namespace Ui {
class ShoppingCartView;
}

class ShoppingCartControl;

class ShoppingCartView : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCartView(ShoppingCartControl *control = 0, QWidget *parent = 0);
    ~ShoppingCartView();

    /* Member Function: viewContentItems
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    bool viewContentItems(QVector<SerializableQObject *>* contentList);

private slots:
    void on_orderButton_clicked();

    void on_backButton_clicked();

private:
    Ui::ShoppingCartView *ui;
    ShoppingCartControl *controller;
    ShoppingCartTable *shoppingCartTable;
};

#endif // SHOPPINGCARTVIEW_H

