#ifndef VIEWCONTROL_H
#define VIEWCONTROL_H

/*
* viewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ViewControl class:
* - Top-level control class for the client interface subsystem
* - Responsible for managing the client user interface
*
* Traceability: CT-014
*
* Acknowledgements: None
*/

#include <QObject>
#include <QWidget>

class ViewControl : public QObject
{
    Q_OBJECT
public:
    explicit ViewControl(QObject *parent = 0);

    bool changeView(ViewType subsystem);

private:
    bool displayView(QWidget widget);
    bool changeWindow(QWidget window);

};

#endif // VIEWCONTROL_H
