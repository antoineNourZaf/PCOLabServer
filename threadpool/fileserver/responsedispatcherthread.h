#ifndef RESPONSEDISPATCHERTHREAD_H
#define RESPONSEDISPATCHERTHREAD_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "response.h"

class ResponseDispatcherThread: public QThread
{
    Q_OBJECT

public:
    ResponseDispatcherThread(AbstractBuffer<Response>* responses, bool hasDebugLog);
protected:
    void run();

private:
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;

signals:
    void responseReady(Response reponse);
};

#endif // RESPONSEDISPATCHERTHREAD_H
