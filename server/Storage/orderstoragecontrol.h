#ifndef ORDERSTORAGECONTROL_H
#define ORDERSTORAGECONTROL_H

/*
* orderstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* OrderStorageControl class:
* - handles the order aspect of the storage system
*
* Traceability: CT-037
*
* Acknowledgements: None
*/

#include <QObject>

class OrderStorageControl : public QObject
{
    Q_OBJECT
public:
    explicit OrderStorageControl(QObject* parent = 0);
};

#endif // ORDERSTORAGECONTROL_H
