#ifndef __TABLE_H__
#define __TABLE_H__

#include "Column.h"

namespace Alfodr
{
    namespace CSV
    {

        /**
         * @brief Tableau Structuré pouvant être exporté en CSV
         * 
         */
        class Table
        {
            public:
                /**
                 * @brief Construct a new Table object
                 * 
                 * @param nbColumns Nombre de colonne par default
                 * @param title Titre de tableau
                 */
                Table(int nbColumns = 0, std::string title =  "");
                
                /**
                 * @brief Destroy the Table object
                 * 
                 */
                ~Table();

                /**
                 * @brief Ajoute une colonne au tableau
                 * 
                 * @warning renvoie une exception (std::string) si la colonne existe déjà
                 * 
                 * @param title Nom de la colone 
                 */
                void addColumn(std::string title);

                /**
                 * @brief Efface le contenu des colonnes
                 * 
                 */
                void cleanAllColums();

                /**
                 * @brief Supprime toutes les colonnes
                 * 
                 */
                void removeAllColums();

                /**
                 * @brief Ajoute une ligne dans le tableau
                 * 
                 * @param line Liste contenant les élément à ajouter
                 */
                void addLine(std::vector<std::string> line);

                /**
                 * @brief Ajoute une ligne dans le tableau
                 * 
                 * @param nbArg nombre d'argument à inséré si inférieur au nombre de ligne
                 * @param ... Liste des élements à ajouté
                 */
                void addLine(int nbArg, ...);
                

                /**
                 * @brief Ajoute une ligne complete dans le tableau
                 * 
                 * @param ... Liste des élements à ajouté
                 */
                #define addLineCplt(...) addLine(-1, __VA_ARGS__)

                #pragma region Accesseur

                    /**
                     * @brief Get the Nb Line object
                     * 
                     * @return size_t Nombre de ligne dans la table
                     */
                    size_t getNbLine() const;

                    /**
                     * @brief Get the Nb Column object
                     * 
                     * @return size_t Nombre de colonne dans la table
                     */
                    size_t getNbColumn() const;

                    /**
                     * @brief Get the Title object
                     * 
                     * @return std::string Titre du tableau
                     */
                    std::string getTitle() const;

                    /**
                     * @brief Convertions en string. Affichage du titre du tableau
                     * 
                     */
                    inline operator std::string() const { return this->getTitle();};

                    /**
                     * @brief Get the Column object
                     * 
                     * @param id de la colonne
                     * @return Column Colonne à l'ID voulut
                     */
                    inline Column getColumn(size_t id) const { return this->columns[id]; };

                    /**
                     * @brief Get the Column object
                     * 
                     * @warning Renvoie une exception (std::string) si aucune colonne n'existe avec ce titre
                     * 
                     * @param title de la colonne
                     * @return Column avec le titre voulut
                     */
                    Column getColumn(std::string title) const;

                    /**
                     * @brief Get the Line object
                     * 
                     * @param line numero de la ligne
                     * @return std::vector<std::string> liste des élements de la ligne 
                     */
                    std::vector<std::string> getLine(size_t line) const;

                #pragma endregion

            protected:

                /**
                 * @brief Colonne du tableau
                 * 
                 */
                std::vector<Column> columns;

            private:

                /**
                 * @brief Titre du tableau
                 * 
                 */
                std::string title;
        };
    }

}
#endif // __TABLE_H__