#include "readerwritercache.h"
#include "option.h"
#include <QDateTime>
#include <QList>
#include <QDebug>
#include <iostream>
ReaderWriterCache::ReaderWriterCache(int invalidationDelaySec, int staleDelaySec):
    invalidationDelaySec(invalidationDelaySec), staleDelaySec(staleDelaySec)
{
    InvalidationTimer *timer = new InvalidationTimer(this);

    timer->run();

    std::cout << "fini" << std::endl;

}

ReaderWriterCache::~ReaderWriterCache()
{
    delete timer;
}

void ReaderWriterCache::putResponse(Response &response) {

    // Creation d'une reponse datée a partir d'une reponse
    TimestampedResponse responseT = {response, (long)time.toTime_t()};

    // Acces en ecriture
    lock.lockWriting();

    // On insère les données dans la cache
    map.insert(response.getRequest().getFilePath(), responseT);

    lock.unlockWriting();
}

Option<Response> ReaderWriterCache::tryGetCachedResponse(Request &request) {

    Option<Response>res = Option<Response>::none();
    QString path = request.getFilePath();

    // Acces en lecture
    lock.lockReading();
    QHash<QString,TimestampedResponse>::iterator it = map.find(path);

    if (it != map.end())
        res = Option<Response>::some(it->response);

    lock.unlockReading();
    return res;
}

void ReaderWriterCache::InvalidationTimer::run() {

    while (true) {

        // Acces en ecriture dans la cache

        std::cout << "notlocked" << std::endl;
        cache->lock.lockWriting();

        std::cout << "locked" << std::endl;
        for (QHash<QString, TimestampedResponse>::iterator i = cache->map.begin(); i != cache->map.end(); ++i){
            // Si la différence de temps entre le placement de la response en cache est
            // maintenant est plus grand que le délais de rafraîchissement, alors la donnée est obsolète
            if ( (cache->time.toTime_t() - i->timestamp) > cache->staleDelaySec){
                cache->map.remove(i->response.getResponse());
            }
        }

        cache->lock.unlockWriting();

        // On attends le temps qu'il faut avant de revérifier l'état de la cache
        sleep(cache->invalidationDelaySec);
    }
}

