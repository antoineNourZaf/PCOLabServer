#include <stdexcept>

template <typename T>
ProdConsBuffer<T>::ProdConsBuffer(unsigned int size)
{
    mutex.release();
    bufferSize = size;
    if ((elements = new T[bufferSize]) != 0) {
        writePointer = readPointer = nbElements = 0;
        nbWaitingProd = nbWaitingConso = 0;
        return;
    } else {
        throw std::invalid_argument("a buffer can't have size 0");
    }
}

template <typename T>
void ProdConsBuffer<T>::put(T item)
{
    mutex.acquire();
    if (nbElements == bufferSize) {
        nbWaitingProd += 1;
        mutex.release();
        waitProd.acquire();
    }
    elements[writePointer] = item;
    writePointer = (writePointer + 1)
    % bufferSize;
    nbElements ++;
    if (nbWaitingConso > 0) {
        nbWaitingConso -= 1;
        waitConso.release();
    }
    else {
        mutex.release();
    }
}

template <typename T>
T ProdConsBuffer<T>::get()
{
    T item;
    mutex.acquire();
    if (nbElements == 0) {
        nbWaitingConso += 1;
        mutex.release();
        waitConso.acquire();
    }
    item = elements[readPointer];
    readPointer = (readPointer + 1)
    % bufferSize;
    nbElements --;
    if (nbWaitingProd > 0) {
        nbWaitingProd -= 1;
        waitProd.release();
    }
    else {
        mutex.release();
    }
    return item;
}

template <typename T>
ProdConsBuffer<T>::~ProdConsBuffer()
{
    delete[] elements;
}
