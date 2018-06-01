#include "requestdispatcherthread.h"

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog)
    : requests(requests), responses(responses), hasDebugLog(hasDebugLog), threadsStarted(0)
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

        // Check if some threads are finished
        for (int i = 0; i < threadsStarted.size(); ++i) {
            if (threadsStarted.at(i)->isFinished()) {
                delete threadsStarted.at(i);
            }
        }
    }
}

void RequestDispatcherThread::requestReady(Request request)
{
    RequestHandlerThread* requestHandlerThread = new RequestHandlerThread(request, responses);
    requestHandlerThread->start();

    //Store the created thread
    threadsStarted.push_back(requestHandlerThread);
}
