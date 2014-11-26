#ifndef COURSEMANAGEMENTVIEW_H
#define COURSEMANAGEMENTVIEW_H

#include <QWidget>

namespace Ui {
class CourseManagementView;
}

class CourseManagementView : public QWidget
{
    Q_OBJECT

public:
    explicit CourseManagementView(QWidget *parent = 0);
    ~CourseManagementView();

private:
    Ui::CourseManagementView *ui;
};

#endif // COURSEMANAGEMENTVIEW_H
