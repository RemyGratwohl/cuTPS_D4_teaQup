#include "contentitemtable.h"

ContentItemTable::ContentItemTable(QObject *parent) :
    ItemTable(parent)
{
}

void ContentItemTable::itemTitleClicked(int row, int col)
{
    if(col == 0) {
        //ui->contentWidget->item(row, col)->setText("D-Clicked");
        for(int i = 0; i < allItems->size(); ++i) {
            ContentItem* content = qobject_cast<ContentItem*>(allItems->at(i));
            QString text = ui->contentWidget->item(row, col)->text();
            if(content->getTitle().compare(text) == 0) {
                selectedItems->push_back(allItems->at(i));
                ui->contentWidget->item(row, 0)->setBackgroundColor(QColor(200, 200, 200));
                ui->contentWidget->item(row, 1)->setBackgroundColor(QColor(200, 200, 200));
                ui->contentWidget->item(row, 2)->setBackgroundColor(QColor(200, 200, 200));
            }
        }
    }
}
