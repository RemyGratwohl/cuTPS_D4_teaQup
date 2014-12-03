#ifndef CONTENTVIEWCONTROL_H
#define CONTENTVIEWCONTROL_H

/*
* contentviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentViewControl class:
* - Manages the ContentView subsystem
*
* Traceability: CT-040
*
* Acknowledgements: None
*/

#include <QObject>
#include "contentview.h"

class ViewControl;

class ContentViewControl : public QObject
{
    Q_OBJECT
public:
    explicit ContentViewControl(ViewControl *viewController = 0, QObject *parent = 0);

    QWidget* getView();
signals:

public slots:

private:
    ViewControl      *viewController;
    ContentView      *contentView;
};

#endif // CONTENTVIEWCONTROL_H

