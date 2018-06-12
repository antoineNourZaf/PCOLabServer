#include "responsedispatcherthread.h"
#include <QDebug>

ResponseDispatcherThread::ResponseDispatcherThread(AbstractBuffer<Response>* responses, bool hasDebugLog)
    : responses(responses), hasDebugLog(hasDebugLog)
{
    if (hasDebugLog)
        qDebug() << "Created response dispatcher thread";
    qRegisterMetaType<Response>("Response");
}

void ResponseDispatcherThread::ResponseDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for responses...";
        Response resp = responses->get();   // block until a response is available
        if (hasDebugLog)
            qDebug() << "Got a response for request '" << resp.getRequest().getFilePath() << "', signalling...";
        responseReady(resp); // send signal
    }
}
