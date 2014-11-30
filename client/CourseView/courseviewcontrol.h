#ifndef COURSEVIEWCONTROL_H
#define COURSEVIEWCONTROL_H

/*
* courseviewcontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* CourseViewControl class:
* - Manages the CourseView subsystem.
*
* Traceability: CT-027
*
* Acknowledgements: None
*/

#include <QObject>

class CourseViewControl : public QObject
{
    Q_OBJECT
public:
    explicit CourseViewControl(QObject *parent = 0);

signals:

public slots:

};

#endif // COURSEVIEWCONTROL_H
