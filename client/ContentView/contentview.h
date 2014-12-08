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

private slots:

    void on_switchToCoursesButton_clicked();

    void on_addButtonButton_clicked();

    void on_add_CancelButton_clicked();

    void on_RemoveBookButton_clicked();

    void on_update_CancelButton_clicked();

    void on_update_UpdateButton_clicked();

    void on_UC_CancelButton_clicked();

    void on_UC_AddSectionButton_clicked();

    void on_ACS_CancelButton_clicked();

    void on_AC_ConfirmButton_clicked();

    void on_AC_CancelButton_clicked();

    void on_l_UpdateBookButton_clicked();

    void on_UB_addChapterbutton_clicked();

private:
    enum PAGE {LIST = 0, UB, AB, AC, UC, ACS, UCS};

    Ui::ContentView *ui;
    ContentViewControl *controller;
};

#endif // CONTENTVIEW_H


