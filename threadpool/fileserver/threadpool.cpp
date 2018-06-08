#include "threadpool.h"
#include "runnablelauncher.h"

ThreadPool::ThreadPool(int maxThreadCount)
    : maxThreadCount(maxThreadCount),idThreadGiven(0),
      isFullBusy(false)
{
    workers    = QVector<RunnableLauncher*>();
    conditions = QVector<Condition*>();
    freeThread = QVector<int>();
    Condition fullBusy;
}

ThreadPool::~ThreadPool() {

}

void ThreadPool::start(Runnable* runnable)
{
    monitorIn();
    int idFree;
    if (freeThread.size() > 0 || !freeThread.isEmpty()) {

        // On prends le premier thread libre disponible
        idFree = freeThread.at(0);

        // On le retire de la liste
        freeThread.pop_front();

        workers.at(idFree)->assignRunnable(runnable);
        // Le thread qui attendait peut se reveiller
        signal(*(conditions[idFree]));
    }
    else {

        // S'il n'y a pas de threads libre on regarde si on a
        // atteint le nombre de threads maximum
        if (workers.size() < maxThreadCount) {

            //Si ce n'est pas le cas on peut en créer d'autres
            RunnableLauncher* worker = new RunnableLauncher(this,idThreadGiven++);
            Condition* cond = new Condition();

            // On les push en meme temps dans les tableaux
            // ainsi ils correspondent entre eux
            workers.push_back(worker);
            conditions.push_back(cond);

            // on lance le thread
            worker->assignRunnable(runnable);
            worker->start();
        } else {
            // Si le nombre max de threads a ete atteint, il faut attendre
            // qu'un thread se libère

            //On signale aux threads qu'il n'y a plus de place ailleurs
            isFullBusy = true;

            //Attentes sur les threads
            wait(fullBusy);

            isFullBusy = false;

            // On prends le premier thread libre disponible
            idFree = freeThread.at(0);

            // On le retire de la liste
            freeThread.pop_front();

            workers.at(idFree)->assignRunnable(runnable);
            // Le thread qui attendait peut se reveiller
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

