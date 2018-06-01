#include "requesthandlerthread.h"

RequestHandlerThread::RequestHandlerThread(Request request, AbstractBuffer<Response>* responses)
    : responses(responses)
{
    requestHandler = new RequestHandler(request, true);
}

void RequestHandlerThread::run()
{
    responses->put(requestHandler->handle());
}

RequestHandlerThread::~RequestHandlerThread()
{
    delete requestHandler;
}
