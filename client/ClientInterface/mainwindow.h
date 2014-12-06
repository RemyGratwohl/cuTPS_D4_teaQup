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
#include <QTableWidgetItem>
#include <QVector>
#include "../server/ServerCommunication/serializableqobject.h"
#include "../server/ContentManagement/contentitem.h"
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

    /* Member Function: viewContentItems
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: contentList is deleted
     * Return Value: Success indicator
     */
    bool viewContentItems(QVector<SerializableQObject *>* contentList);

private slots:
    void on_shoppingCartButton_clicked();
    void on_contentItemTitle_clicked(int row, int col);

private:
    Ui::MainWindow *ui;
    ViewControl  *controller;
};

#endif // MAINWINDOW_H
