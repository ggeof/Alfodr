#ifndef __FILECSV_H__
#define __FILECSV_H__

#include <fstream>
#include <cassert>

#include "Table.h"

namespace Alfodr {

        namespace CSV {

        /**
         * @brief Crée et Ecrit un fichier CSV. 
         * 
         */
        class FileCSV : public Table
        {
            public:
                /**
                * @brief Construct a new @ref FileCSV object
                * 
                * @warning Renvoie une execption (std::string) si l'ouverture du fichier à échoué
                * 
                * @param nameFile Nom du fichier CSV
                */
                FileCSV(std::string nameFile, std::string titleTable = "");
                
                /**
                 * @brief Destroy the @ref FileCSV object
                 * 
                 */
                ~FileCSV();

                /**
                 * @brief Ecrit dans le fichier le tableau
                 * 
                 * @param writeHeaders indicate if the headers must be written
                 */
                void writeInFile(bool writeHeaders);

                /**
                 * @brief Ecrit dans le fichier du texte sur une ligne
                 * 
                 */
                void writeInFile(std::string text);

            private:
                /**
                 * @brief Fichier CSV
                 * 
                 */
                std::ofstream file;

                /**
                 * @brief Indique le nombre de colonne dont le titre à été écrit (-1 : le titre du fichier csv n'a pas été écrit)
                 * 
                 */
                int headerWritten = -1;


                /**
                 * @brief Ecrit l'entete du fichier si ce n'est pas déjà fais
                 * 
                 */
                void writeHeader();

            public :
                
                /**
                 * @brief Charge un fichier CSV
                 * @warning Renvoie une execption (std::string) si l'ouverture du fichier à échoué
                 * 
                 * @param path Chemin du fichier
                 * @param titleColum Les colone possède un titre
                 * @param separator Separator entre les valeur
                 * @return FileCSV Fichier CSV crée
                 */
                static Table fromFileCSV(std::string path, bool titleColumn = false, char separator = ';');

        };

    }
}

#endif // __FILECSV_H__