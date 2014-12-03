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

private:
    Ui::CourseManagementView *ui;
    CourseViewControl *controller;
};

#endif // COURSEMANAGEMENTVIEW_H
