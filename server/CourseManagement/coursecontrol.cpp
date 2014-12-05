#include "coursecontrol.h"
#include <QDebug>
#include "../../client/ClientCommunication/datamessage.h"

CourseControl::CourseControl(ServerDispatcher *d)
    : AbstractManager(d, COURSE), courseStorageControl(0)
{}

bool CourseControl::initialize(void) {
    return CourseStorageControl::getCourseStorageControl(courseStorageControl);
}

bool CourseControl::processMsg(const Message *msg)
{
    QString error;
    ACTION_TYPE msgAction = INVALIDACTION;
    DEST_TYPE msgDest = INVALIDDEST;
    User* user = msg->getUser();

    // Input validation concerning the message dispatching
    // ---------------------------------------------------
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        error = "CourseControl: Error - received a message which is not of type DataMessage.";
        return sendError(msgDest, msgAction, user, error);
    }

    msgAction = dataMessage->getActionType();
    msgDest = dataMessage->getDestType();

    if(msgDest != ownDest) {
        error = "CourseControl: Error - received a message for another subsystem.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the content of the message
    // ------------------------------------------------------
    QVector<SerializableQObject*>* data = dataMessage->getData();
    if( msgAction != RETRIEVE && data->size() < 1 ) {
        error =  "CourseControl: Error - Message data vector has a length less than 1."
                 " Presently, all messages with data are expected to contain at least one item.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Input validation concerning the user
    // ------------------------------------

    if( !user->isOfType(User::CONTENTMGR) && !user->isOfType(User::ADMIN) ) {
        error =  "CourseControl: Error - Non-ContentManager and non-administrator users cannot manage courses.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    bool result = true;
    Term* term0 = 0;
    Course* course0 = 0;
    Term* term1 = 0;

    if( data->size() > 0 ) {
        term0 = qobject_cast<Term*>(data->at(0));
        course0 = qobject_cast<Course*>(data->at(0));

        if( data->size() > 1 ) {
            term1 = qobject_cast<Term*>(data->at(1));
        }
    }
    QVector<SerializableQObject*>* output = 0;

    switch(msgAction)
    {

    case CREATE:
        qDebug() << "CourseControl: received CREATE message.";
        if( course0 == 0 ) {
            error =  "CourseControl: Error - First data item is null or is not a Course.";
            return sendError(msgDest, msgAction, user, error);
        }
        result = addCourse(course0, term1, error);
        break;

    case RETRIEVE:
        qDebug() << "CourseControl: received RETRIEVE message.";
        if( term0 != 0 ) {
            result = getCourses(term0, output, error);
        } else if( course0 == 0 ) {
            result = getTerms(output, error);
        } else {
            error =  "CourseControl: Error - Not expecting to receive a Course as input for RETRIEVE.";
            return sendError(msgDest, msgAction, user, error);
        }
        break;

    case UPDATE:
        qDebug() << "CourseControl: received UPDATE message.";
        if( course0 == 0 ) {
            error =  "CourseControl: Error - First data item is null or is not a Course.";
            return sendError(msgDest, msgAction, user, error);
        }
        result = updateCourse(course0, term1, error);
        break;

    case DELETE:
        qDebug() << "CourseControl: received DELETE message.";
        if( course0 == 0 ) {
            error =  "CourseControl: Error - First data item is null or is not a Course.";
            return sendError(msgDest, msgAction, user, error);
        }
        result = removeCourse(course0, error);
        break;

    default:
        error =  "CourseControl: received unknown message.";
        return sendError(msgDest, msgAction, user, error);
    }

    // Handle errors
    if( !result ) {
        return sendError(msgDest, msgAction, user, error);
    }

    // Dispatch data, if any exists
    if( output != 0 ) {
        return sendData(msgAction, user, output);
    } else {
        return sendSuccess(msgAction, user);
    }
}

bool CourseControl::getCourses(QList<OBJ_ID_TYPE>& courseIDs, QVector<Course*>*& courses, QString& errorMsg) {
    return courseStorageControl->getCourses(courseIDs, courses, errorMsg);
}

bool CourseControl::getTerms(QList<OBJ_ID_TYPE>& termIDs, QVector<Term*>*& terms, QString& errorMsg) {
    return courseStorageControl->getTerms(termIDs, terms, errorMsg);
}

bool CourseControl::addCourse(Course* course, Term* term, QString& errorMsg) {
    return courseStorageControl->addCourse(course, term, errorMsg);
}

bool CourseControl::updateCourse(Course* course, Term* term, QString& errorMsg) {
    return courseStorageControl->updateCourse(course, term, errorMsg);
}

bool CourseControl::removeCourse(Course* course, QString& errorMsg) {
    return courseStorageControl->removeCourse(course, errorMsg);
}

bool CourseControl::getCourses(Term* term, QVector<SerializableQObject*>*& courses, QString& errorMsg) {
    QVector<Course*>* temp = 0;
    if(!courseStorageControl->getCourses(term, temp, errorMsg)) {
        return false;
    }
    courses = new QVector<SerializableQObject*>();
    QVectorIterator<Course*> i(*temp);
    while(i.hasNext()) {
        courses->append(i.next());
    }
    return true;
}

bool CourseControl::getTerms(QVector<SerializableQObject*>*& terms, QString& errorMsg) {
    QVector<Term*>* temp = 0;
    if(!courseStorageControl->getTerms(temp, errorMsg)) {
        return false;
    }
    terms = new QVector<SerializableQObject*>();
    QVectorIterator<Term*> i(*temp);
    while(i.hasNext()) {
        terms->append(i.next());
    }
    return true;
}
