#include "courseviewcontrol.h"
#include "../ClientCommunication/successmessage.h"
#include "../ClientCommunication/datamessage.h"
#include <QDebug>

CourseViewControl::CourseViewControl(ViewControl *vc, ClientDispatcher *d) :
    AbstractViewController(vc, d, COURSE)
{
    view = new CourseManagementView(this);
}

bool CourseViewControl::processMsg(Message *msg)
{
    bool result = true;
    ACTION_TYPE msgAction = msg->getActionType();
    DEST_TYPE msgDest = msg->getDestType();

    if(msgDest != ownDest) {
        qDebug() << "CourseViewControl: Error - received a message for another subsystem.";
        return false;
    }

    // Log success messages
    const SuccessMessage* successMessage = qobject_cast<const SuccessMessage*>(msg);
    if(successMessage != 0) {
        qDebug() << "CourseViewControl: Received success message.";
        return true;
    }

    // At this point, a data message is expected
    const DataMessage* dataMessage = qobject_cast<const DataMessage*>(msg);
    if(dataMessage == 0) {
        qDebug() << "CourseViewControl: Error - received a message which is not of type DataMessage.";
        return false;
    }
    QVector<SerializableQObject*>* data = dataMessage->getData();
    if( data->isEmpty() && msgAction == static_cast<ACTION_TYPE>(COURSEHANDLER_RETRIEVE2) ) {
        qDebug() << "CourseViewControl: Message data vector is empty.";

        QVector<Term*>* emptyTermList = new QVector<Term*>();
        result = receiveTerms(emptyTermList);
        delete emptyTermList;
        return result;
    } else if( data->isEmpty() ) {
        qDebug() << "CourseViewControl: Error - Message data vector is empty for non-RETRIEVE2 operation.";
        return false;
    }

    // Determine which operation to complete and perform it
    // ----------------------------------------------------
    SerializableQObject* item0 = data->first();
    QVectorIterator<SerializableQObject*> itr(*data);
    Term* term = qobject_cast<Term*>(item0);

    switch(msgAction)
    {
    case RETRIEVE:
    {
        qDebug() << "CourseViewControl: received RETRIEVE message.";
        if( term != 0 ) {
            Course* course = 0;
            QVector<Course*>* courses = new QVector<Course*>();
            itr.next(); // Advance to second position
            while(itr.hasNext()) {
                course = qobject_cast<Course*>(itr.next());
                if(course == 0) {
                    result = false;
                    qDebug() <<  "CourseViewControl: Error - Processing list of Courses, but element is not a Course.";
                    break;
                }
                courses->append(course);
            }
            if( result ) {
                result = receiveCourses(term, courses);
            }
            delete courses;

        } else {
            qDebug() <<  "CourseViewControl: Error - No operation found for RETRIEVE action given input data.";
            result = false;
        }
        break;
    }
    case CREATE:
    case UPDATE:
    case DELETE:
    case INVALIDACTION:
    default:
        if( static_cast<quint32>(msgAction) == COURSEHANDLER_RETRIEVE2) {
            qDebug() << "ContentViewControl: received COURSEHANDLER_RETRIEVE2 message.";

            if( term != 0 ) {
                QVector<Term*>* terms = new QVector<Term*>();
                itr.next(); // Advance to second position
                terms->append(term);
                while(itr.hasNext()) {
                    term = qobject_cast<Term*>(itr.next());
                    if(term == 0) {
                        result = false;
                        qDebug() <<  "CourseViewControl: Error - Processing list of Terms, but element is not a Term.";
                        break;
                    }
                    terms->append(term);
                }
                if( result ) {
                    result = receiveTerms(terms);
                }
                delete terms;

            } else {
                qDebug() <<  "CourseViewControl: Error - first data item is not a Term.";
                result = false;
            }

        } else {
            qDebug() << "CourseViewControl: Error - unexpected message action type.";
            result = false;
        }
        break;
    }

    return result;
}

// TODO (Remy or Brandon) Stub implementation
bool CourseViewControl::receiveCourses(Term* term, QVector<Course*>* courses) {
    return false;
}

// TODO (Remy or Brandon) Stub implementation
bool CourseViewControl::receiveTerms(QVector<Term*>* terms) {
    return false;
}

void CourseViewControl::addCourse(Course* course, Term* term) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(course);
    if( term != 0 ) {
        data->append(term);
    }
    sendData(CREATE, data);
}

void CourseViewControl::updateCourse(Course* course, Term* term) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(course);
    if( term != 0 ) {
        data->append(term);
    }
    sendData(UPDATE, data);
}

void CourseViewControl::removeCourse(Course* course) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(course);
    sendData(DELETE, data);
}

void CourseViewControl::requestCourses(Term* term) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    data->append(term);
    sendData(RETRIEVE, data);
}

void CourseViewControl::requestTerms(void) {
    QVector<SerializableQObject*>* data = new QVector<SerializableQObject*>();
    sendData(RETRIEVE, data);
}
