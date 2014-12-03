#include "shoppingcartcontrol.h"

ShoppingCartControl::ShoppingCartControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    shoppingCartView = new ShoppingCartView(this);
}

QWidget* ShoppingCartControl::getView(){
    return shoppingCartView;
}
