#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QObject>

class ShoppingCart : public QObject
{
    Q_OBJECT
public:
    explicit ShoppingCart(QObject *parent = 0);

signals:

public slots:

};

#endif // SHOPPINGCART_H
