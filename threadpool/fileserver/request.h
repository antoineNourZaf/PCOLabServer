#ifndef REQUEST_H
#define REQUEST_H
#include <QString>

/**
 * @brief La classe Request représente une requête que le programme va chercher à traiter
 */
class Request {
private:
    /**
     * @brief filePath chemin de la ressource de la requête que le client cherche à atteindre
     */
    QString filePath;

    /**
     * @brief clientId identifiant du client ayant créé la requête
     */
    QString clientId;

public:
    /**
     * @brief Request constructeur
     */
    Request() {}

    /**
     * @brief Request constructeur
     * @param filePath chemin de la ressource de la requête que le client cherche à atteindre
     * @param clientId identifiant du client ayant créé la requête
     */
    Request(QString filePath, QString clientId): filePath(filePath), clientId(clientId) {}

    /**
     * @brief getFilePath retourne le chemin de la ressource de la requête que le client cherche à atteindre
     * @return le chemin de la ressource de la requête que le client cherche à atteindre
     */
    QString getFilePath() {
        return filePath;
    }

    /**
     * @brief getClientId retourne l'identifiant du client ayant créé la requête
     * @return retourne l'identifiant du client ayant créé la requête
     */
    QString getClientId() {
        return clientId;
    }
};

#endif // REQUEST_H
