#include "contentviewcontrol.h"
#include <QDebug>

ContentViewControl::ContentViewControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    contentView = new ContentView(this);
}

bool ContentViewControl::processMsg(Message *msg)
{
    bool result = true;
    DataMessage* dataMessage = qobject_cast<DataMessage*>(msg);
    ACTION_TYPE msgAction = dataMessage->getActionType();

    switch(msgAction)
    {
    case CREATE:
        qDebug() << "ContentViewControl: received CREATE message.";
        break;
    case RETRIEVE:
        qDebug() << "ContentViewControl: received RETRIEVE message.";
        break;
    case UPDATE:
        qDebug() << "ContentViewControl: received UPDATE message.";
        break;
    case DELETE:
        qDebug() << "ContentViewControl: received DELETE message.";
        break;
    default:
        qDebug() << "ContentViewControl: received incompatible message.";
        result = false;
        break;
    }

    delete dataMessage;
    dataMessage = 0;
    return result;
}

QWidget* ContentViewControl::getView(){
     return contentView;
 }

// TODO (Remy or Brandon) Stub implementation
bool receiveBookList(QVector<SerializableQObject*>* items) {
    return false;
}

// TODO (Remy or Brandon) Stub implementation
bool receiveBookDetails(Book* book, QVector<SerializableQObject*>* items) {
    return false;
}

// TODO (Remy or Brandon) Stub implementation
bool receiveBooks(QVector<SerializableQObject*>* items) {
    return false;
}

// TODO (Bernard) Stub implementation
void addBook(Book* book, Course* course, Term* term) {

}

// TODO (Bernard) Stub implementation
void addChapter(Chapter* chapter) {

}

// TODO (Bernard) Stub implementation
void addSection(ChapterSection* section) {

}

// TODO (Bernard) Stub implementation
void updateBook(Book* book, Course* course, Term* term) {

}

// TODO (Bernard) Stub implementation
void updateChapter(Chapter* chapter) {

}

// TODO (Bernard) Stub implementation
void updateSection(ChapterSection* section) {

}

// TODO (Bernard) Stub implementation
void removeBook(Book* book) {

}

// TODO (Bernard) Stub implementation
void removeChapter(Chapter* chapter) {

}

// TODO (Bernard) Stub implementation
void removeSection(ChapterSection* section) {

}

// TODO (Bernard) Stub implementation
void requestBookList(void) {

}

// TODO (Bernard) Stub implementation
void requestBookDetails(const Book* book) {

}

// TODO (Bernard) Stub implementation
void requestBooks(void) {

}
