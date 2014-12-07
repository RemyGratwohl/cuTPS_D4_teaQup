#ifndef STUDENTVIEW_H
#define STUDENTVIEW_H

#include <QWidget>

class ViewControl;

namespace Ui {
class StudentView;
}

class StudentView : public QWidget
{
    Q_OBJECT

public:
    explicit StudentView(ViewControl *controller = 0);
    ~StudentView();

private:
    Ui::StudentView *ui;
    ViewControl *controller;

};

#endif // STUDENTVIEW_H
