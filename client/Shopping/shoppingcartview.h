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

namespace Ui {
class ShoppingCartView;
}

class ShoppingCartView : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCartView(QWidget *parent = 0);
    ~ShoppingCartView();

private:
    Ui::ShoppingCartView *ui;
};

#endif // SHOPPINGCARTVIEW_H
