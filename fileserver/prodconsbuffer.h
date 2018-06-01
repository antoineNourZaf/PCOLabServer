#ifndef PRODCONSBUFFER_H
#define PRODCONSBUFFER_H
#include "abstractbuffer.h"
#include <QSemaphore>

/**
 * ProdConsBuffer class who implement the productor-consommateur logic.
 * It means it's a buffer who can handle several threads concurrency to his datas
 *
 * The code of this class is directly take from the course
 */
template<typename T>
class ProdConsBuffer : public AbstractBuffer<T> {
protected:
    /**
     * @brief elements array of elements T contained in the buffer
     */
    T *elements;

    /**
     * @brief writePointer pointer in the elements array indicating where the put method will write
     */
    int writePointer;

    /**
     * @brief writePointer pointer in the elements array indicating where the get method will read
     */
    int readPointer;

    /**
     * @brief nbElements counter of the number of current items in the array elements
     */
    int nbElements;

    /**
     * @brief bufferSize maximum size of the array
     */
    int bufferSize;

    /**
     * @brief mutex protect from concurrency the variables of this class
     */
    QSemaphore mutex;

    /**
     * @brief waitProd semaphore where wait the productors when the array is full and we want to put again
     */
    QSemaphore waitProd;

    /**
     * @brief waitConso semaphore where wait the consumers when the array is empty and we want to get an other item
     */
    QSemaphore waitConso;

    /**
     * @brief nbWaitingProd counter of numbers of productors waiting
     */
    unsigned int nbWaitingProd;

    /**
     * @brief nbWaitingConso counter of numbers of consumers waiting
     */
    unsigned int nbWaitingConso;
public:
    /**
     * @brief ProdConsBufferconstructor
     */
    ProdConsBuffer(unsigned int size);

    /**
     * @brief put add an item to the buffer if possible or wait until it's possible
     * @param item the item we wish to add
     */
    void put(T item);

    /**
     * @brief get return and delete from the buffer the "first in" item in the list or wait if there is none
     * @return the "first in" item in the list or wait if there is none
     */
    T get();

    /**
     * @brief ~ProdConsBuffer destructor
     */
    ~ProdConsBuffer();
};
#include "prodconsbuffer.hpp"
#endif // PRODCONSBUFFER_H
