#include "readerwriterlock.h"

ReaderWriterLock::ReaderWriterLock() : mutex(), nbReader(0), nbWriter(0),
    nbWaitingReader(0), nbWaitingWriter(0)
{

}

void ReaderWriterLock::lockReading() {

    mutex.lock();
    while (nbWriter > 0 ) {
        // S'il y a des redacteurs, on attends
        nbWaitingReader++;
        waitingReader.wait(&mutex);
    }

    // On accede à la ressource
    nbReader++;

    // On décrémente la file d'attente
    nbWaitingReader--;

    mutex.unlock();
}

void ReaderWriterLock::unlockReading() {

    mutex.lock();

    // un lecteur est parti
    nbReader--;

    // S'il n'y a pas de lecteurs en attente et accédant à la ressource
    // et s'il y a des redacteurs en attente, on leur permet d'y accéder
    if (nbWaitingWriter > 0 && nbWaitingReader == 0 && nbReader == 0)
        waitingWriter.wakeOne();

    mutex.unlock();
}

void ReaderWriterLock::lockWriting() {

    mutex.lock();

    // Si des lecteurs qui accèdent à la ressource,sont en attente ou
    // s'il y a deja un redacteur, le prochain attends
    while (nbReader > 0 or nbWaitingReader > 0 or nbWriter > 0) {
        // On augmente la file d'attente des redacteurs
        nbWaitingWriter++;
        waitingWriter.wait(&mutex);
    }
    // On accède à la ressource
    nbWriter++;

    // On diminue la file d'attente
    nbWaitingWriter--;

    mutex.unlock();

}

void ReaderWriterLock::unlockWriting() {
    mutex.lock();

    nbWriter--;
    // Si des lecteurs sont en attente, on les reveille
    if (nbWaitingReader > 0 ) {

        waitingReader.wakeAll();

        //Si il n'y a pas de lecteurs en attente et que des
        // redacteurs attendent, on en reveille un qui accede à la ressource
    } else if (nbWaitingWriter > 0) {
        waitingWriter.wakeOne();
    }

    mutex.unlock();
}
