#ifndef __PAIR_H__
#define __PAIR_H__

#include "Objet.h"

// TODO : Gérer les tableaux [...]

namespace Alfodr {
    namespace JSON {

        class _Objet;

        /**
         * @brief Differente type possible for value of a pair
         * 
         */
        enum TYPE_PAIR {
            PAIR_NULL = -1, 
            PAIR_STRING = 0,
            PAIR_BOOL = 1,
            PAIR_NUMBER = 2,
            PAIR_OBJET = 3
        };

        /**
         * @brief Pair of key / value
         * 
         */
        class Pair {
            friend class _Objet;


            public :

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
                Pair(const char * key, char * valueString);

                /**
                 * @brief Construct a new Pair object of type std::shared_ptr<_objet>
                 * 
                 * @param key of the pair
                 * @param pairs std::shared_ptr<_objet> contains in the pair
                 */
                Pair(const char * key, std::shared_ptr<_Objet> pairs);

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
                     * @return bool Indique si la pair est n ull
                     */
                    bool isNull() const;

                    /**
                     * @brief Renvoie la valeur de la pair en boolean
                     * 
                     * @param _default Valeur par default si NULL ou type non convertible en boolean
                     * @return bool Valeur de la pair en bool
                     */
                    bool asBool(bool _default = false) const;

                    /**
                     * @brief Renvoie la valeur de la pair en int
                     * 
                     * @param _default Valeur par default si NULL ou type non convertible en int
                     * @return int Valeur de la pair en int
                     */
                    int asInt(int _default = 0) const;

                    /**
                     * @brief Renvoie la valeur de la pair en double
                     * 
                     * @param _default Valeur par default si NULL ou type non convertible en double
                     * @return double Valeur de la pair en double
                     */
                    double asDouble(double _default = 0.0) const;

                    /**
                     * @brief Renvoie la valeur de la pair en char *
                     * 
                     * @return char* Valeur de la pair en char *
                     */
                    char * asString() const;

                    /**
                     * @brief Renvoie la valeur de la pair en std::shared_ptr<_objet>
                     * 
                     * @return int Valeur de la pair en double
                     */
                    std::shared_ptr<_Objet> asObjet() const;

                    /**
                     * @brief Get the Type of pair
                     * 
                     * @return TYPE_PAIR Type de la pari
                     */
                    TYPE_PAIR getType() const;

                    operator char *() const { return this->asString();};
                    operator bool() const { return this->asBool();};
                    operator double() const { return this->asDouble();};
                    operator int() const { return this->asInt();};
                    operator std::shared_ptr<_Objet>() const { return this->asObjet();};

                    /**
                     * @brief Get the Key object
                     * 
                     * @return const char* Key of the pair
                     */
                    const char * getKey() const;
                #pragma endregion

                #pragma region Mutateur
                    /**
                     * @brief Set the value of the pair with a number
                     * 
                     * @param newValue Nouvelle valeur en double
                     */
                    void setValue(double newValue);

                    /**
                     * @brief Set the value of the pair with a string
                     * 
                     * @param newValue Nouvelle valeur en string
                     */
                    void setValue(char * newValue);

                    /**
                     * @brief Set the value of the pair with a boolean
                     * 
                     * @param newValue Nouvelle valeur en bool
                     */
                    void setValue(bool newValue);

                    /**
                     * @brief Set the value of the pair with a std::shared_ptr<_objet>
                     * 
                     * @param newValue Nouvelle valeur en std::shared_ptr<_Objet> *
                     */
                    void setValue(std::shared_ptr<_Objet> newValue);

                    /**
                     * @brief Set the value of the pair with NULL
                     */
                    void setValueNULL();

                    void operator=(char * value)  { this->setValue(value);};
                    void operator=(bool value) { this->setValue(value);};
                    void operator=(double value) { this->setValue(value);};
                    void operator=(int value) { this->setValue((double)value);};
                    void operator=(std::shared_ptr<_Objet> value) { this->setValue(value);};


                #pragma endregion

            protected :

                /**
                 * @brief Key of the pair
                 * 
                 */
                const char * key;

                /**
                 * @brief Type of the pair
                 * 
                 */
                TYPE_PAIR type;

                /**
                 * @brief Value string of the pair
                 * 
                 */
                char * valueString = NULL;

                /**
                 * @brief std::shared_ptr<_Objet> containing by the pair
                 * 
                 */
                std::shared_ptr<_Objet> pairs = NULL;

                /**
                 * @brief Value of the pair in double
                 * 
                 */
                double valueDouble = 0;
        };
    }
}
#endif // __PAIR_H__