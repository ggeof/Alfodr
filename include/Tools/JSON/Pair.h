#ifndef __PAIR_H__
#define __PAIR_H__

#include "Value.h"

namespace Alfodr {
    namespace JSON {

        class _Objet;

        /**
         * @brief Pair of key / value
         * 
         */
        class Pair : public Value{

            friend class _Objet;

            public :

                /**
                 * @brief Construct a new Pair object with null value from a value
                 *
                 * @param key Clé de la pair
                 * @param value valeur de la pair
                 */
                Pair(const char* key, Value value);

                /**
                 * @brief Construct a new Pair object with null value
                 * 
                 * @param key Clé de la pair
                 */
                Pair(const char * key);

                /**
                 * @brief Construct a new Pair object of type string
                 * 
                 * @param key of the pair
                 * @param valueString value
                 */
                Pair(const char * key, const char * valueString);

                /**
                 * @brief Construct a new Pair object of type string
                 * 
                 * @param key of the pair
                 * @param valueString value
                 */
                Pair(const char * key, std::string valueString);

                /**
                 * @brief Construct a new Pair object of type std::shared_ptr<_objet>
                 * 
                 * @param key of the pair
                 * @param pairs std::shared_ptr<_objet> contains in the pair
                 */
                Pair(const char * key, std::shared_ptr<_Objet> pairs);

                /**
                 * @brief Construct a new Pair object of type std::vector<Value>
                 *
                 * @param key of the pair
                 * @param table std::vector<Value> table
                 */
                Pair(const char* key, std::vector<Value> table);

                /**
                 * @brief Construct a new Pair object of type number
                 * 
                 * @param key of the pair
                 * @param value value of the pair
                 */
                Pair(const char * key, int value);

                /**
                 * @brief Construct a new Pair object of type number
                 * 
                 * @param key of the pair
                 * @param value value of the pair
                 */
                Pair(const char * key, double value);

                /**
                 * @brief Construct a new Pair object of type bool
                 * 
                 * @param key of the pair
                 * @param value of the pair
                 */
                Pair(const char * key, bool value);

                #pragma region Accesseur

                    /**
                     * @brief Get the Key object
                     * 
                     * @return const char* Key of the pair
                     */
                    const char * getKey() const;
                #pragma endregion

            protected :

                /**
                 * @brief Key of the pair
                 * 
                 */
                char key[255];
        };
    }
}
#endif // __PAIR_H__