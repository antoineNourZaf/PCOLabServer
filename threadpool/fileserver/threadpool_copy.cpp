#include "threadpool.h"
#include "runnablelauncher.h"

ThreadPool::ThreadPool(int maxThreadCount)
    : maxThreadCount(maxThreadCount), currentThread(0)
{
    workers    = QVector<RunnableLauncher*>();
    conditions = QVector<Condition*>();
}

ThreadPool::~ThreadPool() {


}

void ThreadPool::start(Runnable* runnable)
{
    monitorIn();

    if (workers.size() < maxThreadCount) {

        RunnableLauncher* worker = new RunnableLauncher(this,currentThread++);
        Condition* cond = new Condition();
        worker->assignRunnable(runnable);
        workers.push_back(worker);
        conditions.push_back(cond);
        worker->start();

    } else {
        // Si tout les threads ont deja été crée on en
        // cherche un qui est disponible
        for (int i = 0; i < workers.size(); ++i) {
            if (workers[i]->isRunnableFinished()) {
                workers[i]->assignRunnable(runnable);
                signal(*(conditions[i]));
            }
        }

    }

    monitorOut();
}

void ThreadPool::waitId(int id) {
    wait(*(conditions[id]));
}
