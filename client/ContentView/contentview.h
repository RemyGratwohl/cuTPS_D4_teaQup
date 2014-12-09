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

    void on_List_RemoveButton_clicked();

    void on_List_AddButton_clicked();

    void on_List_UpdateButton_clicked();

    void on_UB_AddChapterButton_clicked();

    void on_UB_EditChapterButton_clicked();

    void on_UB_RemoveChapterButton_clicked();

    void on_UB_UpdateButton_clicked();

    void on_UB_CancelButton_clicked();

    void on_AB_ConfirmButton_clicked();

    void on_AB_CancelButton_clicked();

    void on_UC_AddSectionButton_clicked();

    void on_UC_UpdateSectionButton_clicked();

    void on_UC_RemoveSectionButton_clicked();

    void on_UC_CancelButton_clicked();

    void on_UC_UpdateButton_clicked();

    void on_ACS_ConfirmButton_clicked();

    void on_ACS_CancelButton_clicked();

    void on_UCS_UpdateButton_clicked();

    void on_UCS_CancelButton_clicked();
    void on_AC_ConfirmButton_clicked();

    void on_AC_CancelButton_clicked();

private:
    enum PAGE {LIST = 0, UB, AB, AC, UC, ACS, UCS};

    Ui::ContentView *ui;
    ContentViewControl *controller;
};

#endif // CONTENTVIEW_H


