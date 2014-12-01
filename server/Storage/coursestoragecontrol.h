#ifndef COURSESTORAGECONTROL_H
#define COURSESTORAGECONTROL_H

/*
* coursestoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* ContentStorageControl class:
* - handles the course aspect of the storage system
*
* Traceability: CT-028
*
* Acknowledgements: None
*/

#include <QObject>

class CourseStorageControl : public QObject
{
    Q_OBJECT
public:
    explicit CourseStorageControl(QObject* parent = 0);
};

#endif // COURSESTORAGECONTROL_H
