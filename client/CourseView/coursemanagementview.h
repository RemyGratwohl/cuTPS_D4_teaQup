#ifndef COURSEMANAGEMENTVIEW_H
#define COURSEMANAGEMENTVIEW_H

/*
* coursemanagementview.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* CourseManagementView class:
* - The user interface class used by a content manager to manage courses.
*
* Traceability: BD-006
*
* Acknowledgements: None
*/


#include <QWidget>
#include "../server/ContentManagement/contentitem.h"
#include "coursetable.h"

namespace Ui {
class CourseManagementView;
}

class CourseViewControl;

class CourseManagementView : public QWidget
{
    Q_OBJECT

public:
    explicit CourseManagementView(CourseViewControl *control = 0, QWidget *parent = 0);
    ~CourseManagementView();

    bool viewContentItems(QVector<Course*>* contentItems);

private slots:
    void on_switchToContentButton_clicked();

    void on_addCourseButton_clicked();

    void on_updateCourseButton_clicked();

    void on_removeCourseButton_clicked();

    void on_add_CancelButton_clicked();

    void on_update_ConfirmButton_clicked();

    void on_update_CancelButton_clicked();

    void on_add_AddButton_clicked();

private:

    enum PAGE {LIST = 0, ADD, UPDATE};

    Ui::CourseManagementView *ui;
    CourseViewControl *controller;
    CourseTable       *courseTable;
};

#endif // COURSEMANAGEMENTVIEW_H
