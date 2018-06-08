#ifndef ABSTRACTBUFFER_H
#define ABSTRACTBUFFER_H

#include "abstractbuffer.h"

/**
 * class abstraite servant de chevront pour tout futur buffer qui en hériteront
 */
template<typename T>
class AbstractBuffer {
public:
    /**
     * @brief put ajoute un élément dans le buffer
     * @param item élément ajouté
     */
    virtual void put(T item) = 0;

    /**
     * @brief get renvoie et supprime un élément du buffer
     * @return l'élément récupéré
     */
    virtual T get() = 0;

    /**
     * @brief tryPut tente de mettre un élément dans le buffer, si celui-ci est plein, abandonne la manipulation
     * @param item élément qu'on tente d'ajouter
     * @return vrai si on réussit à ajouter l'élément
     */
    virtual bool tryPut(T item) = 0;
};

#endif // ABSTRACTBUFFER_H
