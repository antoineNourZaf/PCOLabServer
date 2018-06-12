#ifndef READERWRITERLOCK_H
#define READERWRITERLOCK_H

#include <QWaitCondition>
#include <QMutex>

class ReaderWriterLock
{
private :

    QMutex mutex;
    QWaitCondition waitingWriter, waitingReader;
    int nbReader, nbWriter, nbWaitingReader, nbWaitingWriter;
public:
    ReaderWriterLock();

    void lockReading();
    void lockWriting();
    void unlockReading();
    void unlockWriting();
};

#endif // READERWRITERLOCK_H
