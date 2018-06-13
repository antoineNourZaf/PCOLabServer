#include "requesthandlerrunnable.h"
#include "readerwritercache.h"

RequestHandlerRunnable::RequestHandlerRunnable(Request request, AbstractBuffer<Response>* responses, ReaderWriterCache* cache)
    : responses(responses), cache(cache)
{
    requestHandler = new RequestHandler(request, true);
    req = request;
}

void RequestHandlerRunnable::run()
{

    Response resp;
    Option<Response> cachedResponse = cache->tryGetCachedResponse(req);
    if (cachedResponse.hasValue()) {
        resp = cachedResponse.value();
    } else {
        resp = requestHandler->handle();
        cache->putResponse(resp);
    }
    responses->put(resp);

}


RequestHandlerRunnable::~RequestHandlerRunnable()
{
    delete requestHandler;
}

QString RequestHandlerRunnable::id() {
    return "";
}
