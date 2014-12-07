#include "courseviewcontrol.h"
#include <QDebug>

CourseViewControl::CourseViewControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    courseView = new CourseManagementView(this);
}

bool CourseViewControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "CourseViewControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "CourseViewControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "CourseViewControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "CourseViewControl: received DELETE message.";
        break;
    default:
        qDebug() << "CourseViewControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}

QWidget* CourseViewControl::getView(){
    return courseView;
}

// TODO (Remy or Brandon) Stub implementation
bool receiveCourses(Term* term, QVector<Course*>* courses) {
    return false;
}

// TODO (Remy or Brandon) Stub implementation
bool receiveTerms(QVector<Term*>* terms) {
    return false;
}

// TODO (Bernard) Stub implementation
void addCourse(Course* course, Term* term) {

}

// TODO (Bernard) Stub implementation
void updateCourse(Course* course, Term* term) {

}

// TODO (Bernard) Stub implementation
void removeCourse(Course* course) {

}

// TODO (Bernard) Stub implementation
void requestCourses(Term* term) {

}

// TODO (Bernard) Stub implementation
void requestTerms(void) {

}
