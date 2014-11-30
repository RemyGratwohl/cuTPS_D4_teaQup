#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "userauthenticationcontrol.h"

/*
* loginwindow.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* LoginWindow class:
* - Manages the initial login view that is displayed on client startup.
*
* Traceability: BD-003
*
* Acknowledgements: None
*/

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_connectButton_clicked();

private:
    Ui::LoginWindow *ui;
    UserAuthenticationControl authenticator;
};

#endif // LOGINWINDOW_H
