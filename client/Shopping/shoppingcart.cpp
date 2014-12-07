#include "shoppingcart.h"

ShoppingCart::ShoppingCart(QObject *parent) :
    QObject(parent)
{
    itemsInCart = new QVector<ContentItem*>();
}

bool ShoppingCart::insertNewItems(QVector<ContentItem*>* newItems)
{
    //for(int i = 0; i < newItems->size(); ++i) {
    //    itemsInCart->push_back(newItems->at(i));
    //}
    itemsInCart = newItems;
    return true;
}

QVector<ContentItem*>* ShoppingCart::getShoppingList() const
{
    return itemsInCart;
}
