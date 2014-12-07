#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

/*
* shoppingcart.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ShoppingCart class:
* - Holds references to chosen content items
* - Can be emptied entirely
*
* Traceability: ET-013
*
* Acknowledgements: None
*/


#include <QObject>
#include <QVector>
#include "../server/ServerCommunication/serializableqobject.h"

class ShoppingCart : public QObject
{
    Q_OBJECT
public:
    explicit ShoppingCart(QObject *parent = 0);

    /* Member Function: insertNewItems
     *   Adds these items to the shopping list
     * in: A list of new items to add to the shopping list
     * Side Effects: None
     * Return Value: Success indicator
     */
    bool insertNewItems(QVector<SerializableQObject*>* newItems);

    QVector<SerializableQObject*>* getShoppingList() const;

signals:

public slots:

private:
    QVector<SerializableQObject*>* itemsInCart;
};

#endif // SHOPPINGCART_H
