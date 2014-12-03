#include "courseviewcontrol.h"

CourseViewControl::CourseViewControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    courseView = new CourseManagementView(this);
}

QWidget* CourseViewControl::getView(){
    return courseView;
}
