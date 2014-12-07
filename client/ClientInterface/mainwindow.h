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
#include "../server/ServerCommunication/serializableqobject.h"
#include "../server/ContentManagement/contentitem.h"
#include <../server/UserManagement/user.h>
#include "contentitemtable.h"

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

    bool viewContentItems(QVector<SerializableQObject*>* contentItems);

private slots:
    void on_shoppingCartButton_clicked();

private:
    Ui::MainWindow   *ui;
    ViewControl      *controller;
    ContentItemTable *contentItemTable;
};

#endif // MAINWINDOW_H
