#ifndef USERMANAGEMENTVIEW_H
#define USERMANAGEMENTVIEW_H

/*
* usermanagementview.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* UserManagementView class:
* - The user interface class which allows the modification of users.
*
* Traceability: BD-008
*
* Acknowledgements: None
*/

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
