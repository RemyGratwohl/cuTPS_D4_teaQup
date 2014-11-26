#ifndef SHOPPINGCARTVIEW_H
#define SHOPPINGCARTVIEW_H

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
