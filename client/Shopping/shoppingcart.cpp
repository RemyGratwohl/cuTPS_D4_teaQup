#include "shoppingcart.h"

ShoppingCart::ShoppingCart(QObject *parent) :
    QObject(parent)
{
    itemsInCart = new QVector<SerializableQObject*>();
}

bool ShoppingCart::insertNewItems(QVector<SerializableQObject*>* newItems)
{
    for(int i = 0; i < newItems->size(); ++i) {
        itemsInCart->push_back(newItems->at(i));
    }
    return true;
}

QVector<SerializableQObject*>* ShoppingCart::getShoppingList() const
{
    return itemsInCart;
}
