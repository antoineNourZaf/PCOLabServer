#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "response.h"
#include "request.h"
#include "requesthandlerthread.h"

/**
 * @brief The RequestDispatcherThread class who manage the requests and create the threads who handle them
 */
class RequestDispatcherThread: public QThread
{
    Q_OBJECT

public:
    /**
     * @brief RequestDispatcherThread constructor
     * @param responses prod-cons buffer
     * @param hasDebugLog bool indicating if we want logs
     */
    RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog);

protected:
    /**
     * @brief run read the prod-cons buffer,
     * and each time he found a request,
     * create a handling thread to manage the request
     */
    void run();

private:
    /**
     * @brief requests the prod-cons buffer where we receive the requests
     */
    AbstractBuffer<Request>* requests;
    /**
     * @brief requests the prod-cons buffer where the created thread have to send the response
     */
    AbstractBuffer<Response>* responses;

    /**
     * @brief hasDebugLog the  bool indicating if we want logs
     */
    bool hasDebugLog;

    /**
     * @brief requestReady create a new thread who will manage the request
     * and send the response generated to the response dispatcher
     * @param request that we want to manage
     */
    void requestReady(Request request);
};

#endif // REQUESTDISPATCHERTHREAD_H
