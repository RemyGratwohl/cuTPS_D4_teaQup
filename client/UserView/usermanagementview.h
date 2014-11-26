#ifndef USERMANAGEMENTVIEW_H
#define USERMANAGEMENTVIEW_H

#include <QWidget>

namespace Ui {
class UserManagementView;
}

class UserManagementView : public QWidget
{
    Q_OBJECT

public:
    explicit UserManagementView(QWidget *parent = 0);
    ~UserManagementView();

private:
    Ui::UserManagementView *ui;
};

#endif // USERMANAGEMENTVIEW_H
