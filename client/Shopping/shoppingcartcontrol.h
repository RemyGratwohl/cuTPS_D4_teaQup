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
#include "ClientCommunication/message.h"
#include "ClientCommunication/datamessage.h"

class ViewControl;

class ShoppingCartControl : public QObject
{
    Q_OBJECT
public:
    explicit ShoppingCartControl(ViewControl *viewController = 0, QObject *parent = 0);

    /* Member Function: processMsg
     *   Let the subsystem handle the message
     * in: The message object to handle
     * Side Effects: msg is deleted
     * Return Value: Success indicator
     */
    bool processMsg(Message *msg);

    QWidget* getView();
signals:

public slots:

private:
    ViewControl      *viewController;
    ShoppingCartView *shoppingCartView;
    BillingInfoView  *billingInfoView;
};

#endif // SHOPPINGCARTCONTROL_H
