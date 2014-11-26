#ifndef CONTENTVIEW_H
#define CONTENTVIEW_H

#include <QWidget>

namespace Ui {
class ContentView;
}

class ContentView : public QWidget
{
    Q_OBJECT

public:
    explicit ContentView(QWidget *parent = 0);
    ~ContentView();

private:
    Ui::ContentView *ui;
};

#endif // CONTENTVIEW_H
