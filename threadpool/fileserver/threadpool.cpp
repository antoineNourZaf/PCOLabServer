#include "threadpool.h"
#include "runnablelauncher.h"

ThreadPool::ThreadPool(int maxThreadCount)
    : maxThreadCount(maxThreadCount), currentThread(0), isFullBusy(false)
{
    workers    = QVector<RunnableLauncher*>();
    conditions = QVector<Condition*>();
    Condition fullBusy;
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
                monitorOut();
                return;
            }
        }
        // Si il n'y a aucun de libre, on attend qu'un d'eux se libère
        // On recupere son id et on assigne le runnable
        int idFree = 0;
        isFullBusy = true;
        wait(fullBusy);
        isFullBusy = false;
        if (freeThread.size() > 0){
            idFree = freeThread.at(0);
            freeThread.pop_front();
            workers[idFree]->assignRunnable(runnable);
            signal(*(conditions[idFree]));
        }
    }

    monitorOut();
}

void ThreadPool::waitId(int id) {
    monitorIn();
    wait(*(conditions[id]));
    monitorOut();
}

bool ThreadPool::areThreadBusy() {
    return isFullBusy;
}

void ThreadPool::signalFull(){
    monitorIn();
    signal(fullBusy);
    monitorOut();
}

void ThreadPool::addFreeThread(int id) {
    monitorIn();
    freeThread.push_back(id);
    monitorOut();
}

