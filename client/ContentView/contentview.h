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
