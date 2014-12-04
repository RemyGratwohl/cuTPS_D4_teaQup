#include "coursestoragecontrol.h"

QSharedPointer<CourseStorageControl> CourseStorageControl::courseStorage(new CourseStorageControl());

bool CourseStorageControl::isInitialized = false;
bool CourseStorageControl::initializationAttempted = false;

bool CourseStorageControl::getCourseStorageControl(QSharedPointer<CourseStorageControl>& ptr) {
    if( !initializationAttempted ) {
        initializationAttempted = true;
        isInitialized = courseStorage->initialize();
    }
    if( isInitialized ) {
        ptr = courseStorage;
    }
    return isInitialized;
}


CourseStorageControl::CourseStorageControl(void)
{}

bool CourseStorageControl::initialize(void) {
    return MainStorageControl::getMainStorageControl(mainStorage);
}
