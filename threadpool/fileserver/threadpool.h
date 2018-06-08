#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "hoaremonitor.h"

#include <QVector>

class RunnableLauncher;

class ThreadPool : public HoareMonitor {
public:

    ThreadPool(int maxThreadCount);
    ~ThreadPool();

    /* Start a runnable. If a thread in the pool is available, assign the
    runnable to it. If no thread is available but the pool can grow,
    create a new pool thread and assign the runnable to it. If no
    thread is available and the pool is at max capacity, block the
    caller until a thread becomes available again. */
    void start(Runnable* runnable);


    void waitId(int id);
    bool areThreadBusy();
    void signalFull();
    void addFreeThread(int id);

private:

    int maxThreadCount;
    int currentThread;
    QVector<RunnableLauncher*> workers;
    QVector<Condition*> conditions;
    QVector<int> freeThread;
    bool isFullBusy;
    Condition fullBusy;

};

#endif // THREADPOOL_H
