#include "requestdispatcherthread.h"
#include "threadpool.h"
#include "requesthandlerrunnable.h"

#define MAX_THREADS QThread::idealThreadCount()
#define INVALIDATION_TIME 120
#define REFRESH_TIME 5
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
    ReaderWriterCache* cache = new ReaderWriterCache(REFRESH_TIME, INVALIDATION_TIME);

    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request req = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request from client id :'" << req.getClientId() << "', treatment...";

        // On passe la requete au thread pool qui va lui meme
        // l'assigner a un thread pour la traiter.
        requestReady(req, pool, cache);

    }
}

void RequestDispatcherThread::requestReady(Request request, ThreadPool* pool, ReaderWriterCache* cache)
{

    RequestHandlerRunnable* requestHandlerThread = new RequestHandlerRunnable(request, responses, cache);
    pool->start(requestHandlerThread);

}
