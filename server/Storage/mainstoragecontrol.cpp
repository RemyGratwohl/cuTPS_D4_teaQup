#include "mainstoragecontrol.h"

MainStorageControl::MainStorageControl(QObject *parent)
    : QObject(parent)
{
    contentControl = new ContentStorageControl(this);
    courseControl  = new CourseStorageControl(this);
    orderControl   = new OrderStorageControl(this);
    userControl    = new UserStorageControl(this);
}
