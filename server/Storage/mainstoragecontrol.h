#ifndef MAINSTORAGECONTROL_H
#define MAINSTORAGECONTROL_H

/*
* mainstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* MainStorageControl class:
* - handles all of the aspects of the storage system
* - is the main control for the storage system,
*   interacts with the other storage controls.
*
* Traceability: CT-035
*
* Acknowledgements: None
*/

#include <QObject>
#include "contentstoragecontrol.h"
#include "coursestoragecontrol.h"
#include "orderstoragecontrol.h"
#include "userstoragecontrol.h"

class MainStorageControl : public QObject
{
    Q_OBJECT
public:
    explicit MainStorageControl(QObject* parent = 0);

private:
    ContentStorageControl* contentControl;
    CourseStorageControl*  courseControl;
    OrderStorageControl*   orderControl;
    UserStorageControl*    userControl;
};

#endif // MAINSTORAGECONTROL_H
