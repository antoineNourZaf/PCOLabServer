#ifndef QFILEREADER_H
#define QFILEREADER_H
#include <QFileInfo>
#include <QTextStream>

/**
 * @brief la classe FileReader permet de simuler une requête lourde en charge de travail pour cette application,
 * afin de mieux visualiser les effets
 */
class FileReader
{
public:
    /**
     * @brief FileReader constructeur
     * @param path chemin du fichier lu
     * @param debug
     */
    FileReader(const QString path, bool debug = false);

    /**
     * @brief fileExists permet de vérifier si le fichier existe à l'emplacement path
     * @return vrai si le chemin existe
     */
    bool fileExists();
    int byteCount();
    QString readAll();

private:
    void simulateHeavyEncoding();
    QFileInfo info;
    bool debug;
};

#endif // QFILEREADER_H
