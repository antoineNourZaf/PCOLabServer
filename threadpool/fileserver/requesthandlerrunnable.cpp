#include "requesthandlerrunnable.h"

RequestHandlerRunnable::RequestHandlerRunnable(Request request, AbstractBuffer<Response>* responses)
    : responses(responses)
{
    requestHandler = new RequestHandler(request, true);
}

void RequestHandlerRunnable::run()
{
    responses->put(requestHandler->handle());
}


RequestHandlerRunnable::~RequestHandlerRunnable()
{
    delete requestHandler;
}

QString RequestHandlerRunnable::id() {
    return "";
}
