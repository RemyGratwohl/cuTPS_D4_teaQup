#ifndef COURSETABLE_H
#define COURSETABLE_H

#include <QObject>
#include <QTableWidget>
#include "../server/CourseManagement/course.h"
#include <QPushButton>

class CourseTable : public QObject
{
    Q_OBJECT
public:
    explicit CourseTable(QObject *parent = 0, QTableWidget* table = 0);

    ~CourseTable();

    /* Member Function: updateTableView
     *   Displayes the names of content items in a list
     * in: A list of content items to view
     * Side Effects: None
     * Return Value: Success indicator
     */
    bool updateTableView(QVector<Course*>* contentList);

    bool initialize(QPushButton *editButton);

    bool isItemSelected();

signals:

public slots:
    void itemClicked(int row, int col);

protected:
    QTableWidget *contentTable;
    QVector<Course*>* allItems;
    QPushButton* editCourseButton;

private:
    bool handleEditButton();
};

#endif // COURSETABLE_H
