#include "requestdispatcherthread.h"
#include "threadpool.h"
#include "requesthandlerthread.h"
#define MAX_THREADS QThread::idealThreadCount()

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog)
    : requests(requests), responses(responses), hasDebugLog(hasDebugLog), threadsStarted(0)
{
    if (hasDebugLog)
        qDebug() << "Created response dispatcher thread";
    qRegisterMetaType<Response>("Response");
}

void RequestDispatcherThread::run()
{
    ThreadPool* pool = new ThreadPool(MAX_THREADS);

    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request from client id :'" << req.getClientId() << "', treatment...";

        // On passe la requete au thread pool qui va lui meme
        // l'assigner a un thread pour la traiter.
        requestReady(req, pool);

    }
}

void RequestDispatcherThread::requestReady(Request request, ThreadPool* pool)
{

    RequestHandlerThread* requestHandlerThread = new RequestHandlerThread(request, responses);
    pool->start(requestHandlerThread);

}
