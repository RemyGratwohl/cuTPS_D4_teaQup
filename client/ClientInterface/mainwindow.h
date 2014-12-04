#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
* mainwindow.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* MainWindow class:
* - Displays other subsystems' unique view widgets.
*
* Traceability: BD-001
*
* Acknowledgements: None
*/

#include <QMainWindow>
#include <../server/UserManagement/user.h>

class ViewControl;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ViewControl *controller = 0);
    ~MainWindow();

private slots:
    void on_shoppingCartButton_clicked();

private:
    Ui::MainWindow *ui;
    ViewControl  *controller;
};

#endif // MAINWINDOW_H
