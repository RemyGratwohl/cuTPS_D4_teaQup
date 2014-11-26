#ifndef SERVERDISPATCHER_H
#define SERVERDISPATCHER_H

#include <QObject>

class ServerDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit ServerDispatcher(QObject *parent = 0);

signals:

public slots:

};

#endif // SERVERDISPATCHER_H
