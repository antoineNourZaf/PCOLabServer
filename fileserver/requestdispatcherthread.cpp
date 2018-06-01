#include "requestdispatcherthread.h"

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog)
    : requests(requests), responses(responses), hasDebugLog(hasDebugLog)
{
    if (hasDebugLog)
        qDebug() << "Created response dispatcher thread";
    qRegisterMetaType<Response>("Response");
}

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request from client id :'" << req.getClientId() << "', treatment...";
        requestReady(req); // create a new thread to handle the request
    }
}

void RequestDispatcherThread::requestReady(Request request)
{
    RequestHandlerThread requestHandlerThread(request, responses);
    requestHandlerThread.start();
}
