#ifndef RUNNABLELAUNCHER_H
#define RUNNABLELAUNCHER_H

#include <QThread>
#include "runnable.h"
#include "threadpool.h"

class RunnableLauncher : public QThread {
private:

    ThreadPool* _monitor;
    int id;
    Runnable* _runnable;
    bool finishRun;

public:

    RunnableLauncher(ThreadPool* monitor, int id);
    ~RunnableLauncher();
    bool isRunnableFinished();
    void assignRunnable(Runnable* runnable);
    void run() override;
};

#endif // RUNNABLELAUNCHER_H
