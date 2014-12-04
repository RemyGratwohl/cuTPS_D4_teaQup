#include "contentstoragecontrol.h"

QSharedPointer<ContentStorageControl> ContentStorageControl::contentStorage(new ContentStorageControl());

bool ContentStorageControl::isInitialized = false;
bool ContentStorageControl::initializationAttempted = false;

bool ContentStorageControl::getContentStorageControl(QSharedPointer<ContentStorageControl>& ptr) {
    if( !initializationAttempted ) {
        initializationAttempted = true;
        isInitialized = contentStorage->initialize();
    }
    if( isInitialized ) {
        ptr = contentStorage;
    }
    return isInitialized;
}


ContentStorageControl::ContentStorageControl(void)
{}

bool ContentStorageControl::initialize(void) {
    return MainStorageControl::getMainStorageControl(mainStorage);
}

bool ContentStorageControl::addBook(Book* book) {
    return false;
}

bool ContentStorageControl::addChapter(Chapter* chapter) {
    return false;
}

bool ContentStorageControl::addSection(ChapterSection* section) {
    return false;
}

bool ContentStorageControl::updateBook(Book* book) {
    return false;
}

bool ContentStorageControl::updateChapter(Chapter* chapter) {
    return false;
}

bool ContentStorageControl::updateSection(ChapterSection* section) {
    return false;
}

bool ContentStorageControl::removeBook(Book* book) {
    return false;
}

bool ContentStorageControl::removeChapter(Chapter* chapter) {
    return false;
}

bool ContentStorageControl::removeSection(ChapterSection* section) {
    return false;
}

bool ContentStorageControl::getBookList(User* student, QVector<Book*>*& items) {
    return false;
}

bool ContentStorageControl::getChapters(Book* book, QVector<Chapter*>*& items) {
    return false;
}

bool ContentStorageControl::getSections(Chapter* chapter, QVector<ChapterSection*>*& items) {
    return false;
}

bool ContentStorageControl::getBooks(QVector<Book*>*& items) {
    return false;
}
