#ifndef SHOPPINGCARTCONTROL_H
#define SHOPPINGCARTCONTROL_H

/*
* shoppingcartcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ShoppingCartControl class:
* - Manages the shopping subsystem
*
* Traceability: CT-016
*
* Acknowledgements: None
*/

#include <QObject>

class ShoppingCartControl : public QObject
{
    Q_OBJECT
public:
    explicit ShoppingCartControl(QObject *parent = 0);

signals:

public slots:

};

#endif // SHOPPINGCARTCONTROL_H
