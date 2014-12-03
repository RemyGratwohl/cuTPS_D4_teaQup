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
#include "shoppingcartview.h"
#include "billinginfoview.h"

class ViewControl;

class ShoppingCartControl : public QObject
{
    Q_OBJECT
public:
    explicit ShoppingCartControl(ViewControl *viewController = 0, QObject *parent = 0);

    QWidget* getView();
signals:

public slots:

private:
    ViewControl      *viewController;
    ShoppingCartView *shoppingCartView;
    BillingInfoView  *billingInfoView;
};

#endif // SHOPPINGCARTCONTROL_H
