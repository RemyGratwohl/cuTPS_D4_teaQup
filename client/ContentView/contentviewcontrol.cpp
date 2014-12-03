#include "contentviewcontrol.h"

ContentViewControl::ContentViewControl(ViewControl *viewController, QObject *parent) :
    viewController(viewController),
    QObject(parent)
{
    contentView = new ContentView(this);
}

QWidget* ContentViewControl::getView(){
     return contentView;
 }
