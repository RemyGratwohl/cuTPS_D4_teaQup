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

// Untested
bool CourseStorageControl::getCourses(QList<OBJ_ID_TYPE>& courseIDs, QVector<Course*>*& courses, QString& errorMsg) {

    courses = new QVector<Course*>();

    foreach(const OBJ_ID_TYPE cid, courseIDs) {
        QString query = "Select * from course where courseid=" + QString::number(cid);
        QSqlQuery result = mainStorage->runQuery(query);

        if(result.lastError().text().length() > 1){
            errorMsg = result.lastError().text();
            return false;
        }
        if(!result.first()){
            // If there are no results and there were no errors, then the course does not exist.
            errorMsg = "Course ID:" + QString::number(cid) + " does not exist.";
            // Iterate through and delete or just push back an empty course and display the error to the user?
            return false;
        }


        if(result.first()){
            Course* newCourse = new Course();
            QString name = result.value("name").toString();
            newCourse->setName(name);
            quint64 termid = result.value("termid").toInt();
            newCourse->setTermID(termid);
            newCourse->setID(cid);
            courses->push_back(newCourse);
        }
    }



    return true;
}

// Untested
bool CourseStorageControl::getTerms(QList<OBJ_ID_TYPE>& termIDs, QVector<Term*>*& terms, QString& errorMsg) {

    terms = new QVector<Term*>();

    foreach(const OBJ_ID_TYPE tid, termIDs) {
        QString query = "Select * from term where termid=" + QString::number(tid);
        QSqlQuery result = mainStorage->runQuery(query);

        if(result.lastError().text().length() > 1){
            errorMsg = result.lastError().text();
            return false;
        }

        if(!result.first()){
            // If there are no results and there were no errors, then the term does not exist.
            errorMsg = "Term ID:" + QString::number(tid) + " does not exist.";
            // Iterate through and delete or just push back an empty course and display the error to the user?
            return false;
        }

        if(result.first()){
            Term* newTerm = new Term();
            QString semester = result.value("semester").toString();
            newTerm->setSemester(semester);
            quint16 termYear = result.value("term_year").toInt();
            newTerm->setYear(termYear);
            newTerm->setID(tid);
            terms->push_back(newTerm);
        }
    }

    return true;
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

// Untested
bool CourseStorageControl::getCourses(Term* term, QVector<Course*>*& courses, QString& errorMsg) {
    quint16 termid = term->getID();

    courses = new QVector<Course*>();

    QString query = "Select * from course where termid=" + QString::number(termid);
    QSqlQuery result = mainStorage->runQuery(query);

    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }
    if(!result.first()){
        // If there are no results and there were no errors, then there are no courses that term, and the term will be removed.
        errorMsg = "Term ID:" + QString::number(termid) + " does not exist. Removing.";
        // Delete term from DB here
        return false;
    }


    while(result.next()){
        Course* newCourse = new Course();
        QString name = result.value("name").toString();
        newCourse->setName(name);
        quint64 courseid = result.value("courseid").toInt();
        newCourse->setID(courseid);
        newCourse->setTermID(termid);
        courses->push_back(newCourse);
    }

    return true;
}

// Untested
bool CourseStorageControl::getTerms(QVector<Term*>*& terms, QString& errorMsg) {

    QString query = "Select * from term";
    QSqlQuery result = mainStorage->runQuery(query);

    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }

    if(!result.first()){
        // If there are no results and there were no errors, then there are no terms.
        return true;
    }

    terms = new QVector<Term*>();
    while(result.next()){
        Term* newTerm = new Term();
        quint64 termid = result.value("termid").toInt();
        newTerm->setID(termid);
        QString semester = result.value("semester").toString();
        newTerm->setSemester(semester);
        quint16 termYear = result.value("term_year").toInt();
        newTerm->setYear(termYear);

        terms->push_back(newTerm);
    }

    return true;
}
