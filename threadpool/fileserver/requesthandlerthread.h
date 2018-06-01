#ifndef REQUESTHANDLERTHREAD_H
#define REQUESTHANDLERTHREAD_H

#include "qthread.h"
#include "request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "requesthandler.h"

/**
 * @brief The RequestHandlerThread class represent a thread who will manage one request and put the response in the given response buffer
 */
class RequestHandlerThread : public QThread {
private:
    /**
     * @brief responses buffer where the response will be stored
     */
    AbstractBuffer<Response>* responses;

    /**
     * @brief requestHandler request handler who is able to manage the request
     */
    RequestHandler* requestHandler;

public:
    /**
     * @brief RequestHandlerThread constructor
     * @param request that the thread have to manage
     * @param responses buffer where the response will be stored
     */
    RequestHandlerThread(Request request, AbstractBuffer<Response>* responses);

    /**
      * @brief destructor
      */
    ~RequestHandlerThread();
protected:
    /**
     * @brief run start the managing of the request and put in the responses buffer when finished
     */
    void run();

};
#endif // REQUESTHANDLERTHREAD_H
