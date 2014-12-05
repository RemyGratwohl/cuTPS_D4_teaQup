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

bool CourseStorageControl::getCourses(QList<OBJ_ID_TYPE>& courseIDs, QVector<Course*>*& courses, QString& errorMsg) {
    return false;
}

bool CourseStorageControl::getTerms(QList<OBJ_ID_TYPE>& termIDs, QVector<Term*>*& terms, QString& errorMsg) {
    return false;
}

bool CourseStorageControl::addCourse(Course* course, Term* term, QString& errorMsg) {
    return false;
}

bool CourseStorageControl::updateCourse(Course* course, Term* term, QString& errorMsg) {
    return false;
}

bool CourseStorageControl::removeCourse(Course* course, QString& errorMsg) {
    return false;
}

bool CourseStorageControl::getCourses(Term* term, QVector<SerializableQObject*>*& courses, QString& errorMsg) {
    return false;
}

bool CourseStorageControl::getTerms(QVector<SerializableQObject*>*& terms, QString& errorMsg) {
    return false;
}
