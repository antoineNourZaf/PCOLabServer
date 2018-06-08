#include "runnablelauncher.h"

RunnableLauncher::RunnableLauncher(ThreadPool* monitor, int id) :
    _monitor(monitor), id(id), _runnable(nullptr), finishRun(false)
{ }

RunnableLauncher::~RunnableLauncher() {
    if (_runnable != nullptr) {
        delete _runnable;
        _runnable = nullptr;
    }
}

void RunnableLauncher::assignRunnable(Runnable *runnable) {
    _runnable = runnable;
}

void RunnableLauncher::run() {
    while (true) {
        if (_runnable != nullptr) {
            _runnable->run();

            //Le runnable a fini de s'executer, on le supprime
            delete _runnable;
            _runnable = nullptr;
            finishRun = true;

            _monitor->addFreeThread(id);

            // Si tout les threads étaient occupés, on signale
            // qu une place est disponible

            if (_monitor->areThreadBusy()){
                _monitor->signalFull();

            }
            // Une fois le runnable fini, on le fait patienter en attendant
            // Qu'un autre runnable arrive
            _monitor->waitId(id);
        }
    }

}

bool RunnableLauncher::isRunnableFinished() {
    return finishRun;
}
