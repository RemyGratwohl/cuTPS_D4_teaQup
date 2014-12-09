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

    if(course->getTermID() == 0 && term == 0){
        errorMsg = "Either a new term must be sent in, or an existing termID must be sent with the course.";
        return false;
    }
    bool existsTerm = true;
    bool existsCourse = true;
    QString termid = "??";
    QString semester = "";
    QString courseid = "??";

    // Verify Term
    if(!isTerm(term, termid)){
        existsTerm = false;

        // Get latest ID and set that to termid
        termid = QString::number(mainStorage->getLatestID("termid", "term"));
        if(term->getSemester() == "Fall")
            semester = "F";
        else if(term->getSemester() == "Winter")
            semester = "W";
        else if(term->getSemester() == "Summer")
            semester = "S";
        else {
            // There's an error with the Term object
            errorMsg = "Error with Term object.";
            return false;
        }
    }

    // Verify Course
    course->setTermID(termid.toInt());

    if(!isCourse(course, courseid)){
        existsCourse = false;
        qDebug() << "Course does not exist!";
        // Get latest ID and set that to courseid
        courseid = QString::number(mainStorage->getLatestID("courseid", "course"));
    }

    if(mainStorage->getMainStorage().open()){
        mainStorage->getMainStorage().transaction();
        QSqlQuery prepQ;
        if(!existsTerm){
            // Add term to DB
            prepQ.prepare("insert into term (termid, semester, term_year) values (:termid, :semester, :term_year)");
            prepQ.bindValue(":termid", termid.toInt());
            prepQ.bindValue(":semester", semester);
            prepQ.bindValue(":term_year", term->getYear());
            if(prepQ.exec()){
                qDebug() << "COSC | (Term)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                qDebug() << "Add Term Failed";
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        if(!existsCourse){
            // Add Course to DB
            prepQ.prepare("insert into course (courseid, name, termid) values (:courseid, :name, :termid)");
            prepQ.bindValue(":termid", termid.toInt());
            prepQ.bindValue(":courseid", courseid.toInt());
            prepQ.bindValue(":name", course->getName());
            if(prepQ.exec()){
                qDebug() << "COSC | (Course)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
            }
            else{
                mainStorage->getMainStorage().rollback();
                mainStorage->getMainStorage().close();
                errorMsg = prepQ.lastError().text();
                return false;
            }
        }

        if(!mainStorage->getMainStorage().commit())
        {
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = "Commit failed: " + prepQ.lastError().text();
            return false;
        }
        else {
            qDebug() << "Everything went great.";
            mainStorage->getMainStorage().close();
            return true;
        }
    }
    else{
        errorMsg = "COSC | addCourse(): Database failed to open!";
        return false;
    }

    return false;
}

bool CourseStorageControl::updateCourse(Course* course, Term* term, QString& errorMsg) {
    if(mainStorage->getMainStorage().open()){
        mainStorage->getMainStorage().transaction();
        QSqlQuery prepQ;
        prepQ.prepare("update term set termid=:termid, semester=:semester, term_year=:term_year");
        prepQ.bindValue(":termid", term->getID());
        prepQ.bindValue(":semester", term->getSemester());
        prepQ.bindValue(":term_year", term->getYear());
        if(prepQ.exec()){
            qDebug() << "CISC | (Term)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }

        prepQ.prepare("update course set courseid=:courseid, name=:name, termid=:termid");
        prepQ.bindValue(":termid", term->getID());
        prepQ.bindValue(":courseid", course->getID());
        prepQ.bindValue(":name", course->getName());
        if(prepQ.exec()){
            qDebug() << "CISC | (Course)Number of rows affected: " + QString::number(prepQ.numRowsAffected());
        }
        else{
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = prepQ.lastError().text();
            return false;
        }

        if(!mainStorage->getMainStorage().commit())
        {
            mainStorage->getMainStorage().rollback();
            mainStorage->getMainStorage().close();
            errorMsg = "Commit failed: " + prepQ.lastError().text();
            return false;
        }
        else {
            qDebug() << "Everything went great.";
            mainStorage->getMainStorage().close();
            return true;
        }
    }


    else {
        errorMsg = "failed to open";
        return false;
    }
    return false;
}

// Untested
bool CourseStorageControl::removeCourse(Course* course, QString& errorMsg) {
    QString query;

    query = "Delete from course where courseid=" + QString::number(course->getID());

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);
    query = "Delete from course_book where courseid=" + QString::number(course->getID());

    // Run query and get result set object
    result = mainStorage->runQuery(query);
    query = "Delete from course_user where courseid=" + QString::number(course->getID());

    // Run query and get result set object
    result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        errorMsg = result.lastError().text();
        return false;
    }
    if(result.numRowsAffected()  < 1){
        qDebug() << "Nothing was removed";
    }

    qDebug() << "REMOVED: " + QString::number(result.numRowsAffected());
    return true;
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

bool CourseStorageControl::isTerm(Term *term, QString& id) {

    QString query;
    QString semester;

    if(term->getSemester() == "Fall")
        semester = "F";
    else if(term->getSemester() == "Winter")
        semester = "W";
    else if(term->getSemester() == "Summer")
        semester = "S";
    else // There's an error with the Term object
        return false;

    query = "Select termid from term where semester='" + semester + "' AND term_year=" + QString::number(term->getYear());

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    if(result.first()){
        id = result.value("termid").toString();
        return true;
    }
    // If there is more than one user returned, return false because something is wrong with the database
    else if (result.next()){
        return false;
    }
    // If there are no results and there were no errors, then the term does not exist.
    else {
        return false;
    }

    //Should never reach here
    qDebug() << "???";
    return false;
}

bool CourseStorageControl::isCourse(Course* course, QString& id){
    QString query;

    query = "Select courseid from course where termid=" + QString::number(course->getTermID()) + " AND name='" + course->getName() + "'";

    // Run query and get result set object
    QSqlQuery result = mainStorage->runQuery(query);

    // lastError() is a string with a length of one (I think it might be a space?)
    // Strangest thing: QString.empty() returns false. Thus why the >1 check.
    if(result.lastError().text().length() > 1){
        qDebug() << result.lastError();
        return false;
    }

    if(result.first()){
        id = result.value("courseid").toString();
        return true;
    }
    // If there is more than one user returned, return false because something is wrong with the database
    else if (result.next()){
        return false;
    }
    // If there are no results and there were no errors, then the term does not exist.
    else {
        return false;
    }

    //Should never reach here
    qDebug() << "???";
    return false;
}
