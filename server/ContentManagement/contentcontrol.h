#ifndef CONTENTCONTROL_H
#define CONTENTCONTROL_H

/*
* contentcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentControl class:
* - handles all operations on content items in the server
*
* Traceability: CT-039
*
* Acknowledgements: None
*/

#include <QObject>

class ContentControl : public QObject
{
    Q_OBJECT
public:
    explicit ContentControl(QObject* parent = 0);
};

#endif // CONTENTCONTROL_H
