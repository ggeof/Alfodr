#ifndef __COLONNE_H__
#define __COLONNE_H__

#include <iostream>
#include <vector>

namespace Alfodr
{

    namespace CSV
    {

        /**
         * @brief Colonne d'un fichier CSV
         * 
         */
        class Column
        {
            friend class Table;

            public:
                /**
                 * @brief Construct a new @ref Colonne object
                 * 
                 * @param _header Nom de la colonne
                 */
                Column(std::string _header);

                /**
                 * @brief Ajoute un élément dans la colonne
                 * 
                 * @param elem A ajouter
                 */
                void addElement(std::string elem);

                /**
                 * @brief Vide la colonne
                 * 
                 */
                void cleanColumn();


                /**
                 * @brief Convertions en string. Affichage du nom de la colonne
                 * 
                 */
                inline operator std::string() const { return this->title;};

                /**
                 * @brief Get the Title object
                 * 
                 * @return std::string Titre de la colonne
                 */
                std::string getTitle() const;

                /**
                 * @brief Get the Element object
                 * 
                 * @param id de l'élément
                 * @return std::string Element retournée
                 */
                inline std::string getElement(size_t id) const {return this->elems[id]; };

                /**
                 * @brief Get the Nb Element object
                 * 
                 * @return size_t Nombre d'élément dans la colonne
                 */
                inline size_t getNbElement() const { return this->elems.size(); }; 

            private:
                /**
                 * @brief Nom de l'en-tête de la colonne
                 * 
                 */
                std::string title;

                /**
                 * @brief Vecteur contenant tout les éléments de la colonne
                 * 
                 */
                std::vector<std::string> elems;
        };
    }
}

#endif // __COLONNE_H__