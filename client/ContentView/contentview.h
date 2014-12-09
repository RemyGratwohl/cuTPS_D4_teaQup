#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

/*
* contentview.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentView class:
* - UI class used by Content Manager's to create,modify, and delete Content Itemss
*
* Traceability: BD-009
*
* Acknowledgements: None
*/

#include <QWidget>
#include "bookcontenttable.h"
#include "../server/ContentManagement/book.h"

namespace Ui {
class ContentView;
}

class ContentViewControl;

class ContentView : public QWidget
{
    Q_OBJECT
public:
    explicit ContentView(ContentViewControl *control = 0, QWidget *parent = 0);
    ~ContentView();

    bool viewContentItems(QVector<Book *> *contentItems);

private slots:
    void on_pushButton_2_clicked();

    void on_switchToCoursesButton_clicked();

    void on_addButtonButton_clicked();

    void on_add_CancelButton_clicked();

    void on_RemoveBookButton_clicked();

private:
    Ui::ContentView *ui;
    ContentViewControl *controller;
    BookContentTable *bookContentTable;
};

#endif // CONTENTVIEW_H


