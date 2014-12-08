#ifndef BILLINGINFOVIEW_H
#define BILLINGINFOVIEW_H


/*
* billinginfoview.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* BillingInfoView class:
* - The user interface class which collects student billing information
*
* Traceability: BD-005
*
* Acknowledgements: None
*/

#include <QWidget>

namespace Ui {
class BillingInfoView;
}

class ShoppingCartControl;

class BillingInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit BillingInfoView(ShoppingCartControl *control = 0, QWidget *parent = 0);
    ~BillingInfoView();

private slots:
    void on_backButton_clicked();

    void on_orderButton_clicked();

private:
    Ui::BillingInfoView *ui;
    ShoppingCartControl *controller;
};

#endif // BILLINGINFOVIEW_H
