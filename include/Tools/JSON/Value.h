#ifndef __VALUE_H__
#define __VALUE_H__

#include "Objet.h"

#include <string>

namespace Alfodr {
    namespace JSON {

        class _Objet;

        /**
         * @brief Differente type possible for value
         * 
         */
        enum TYPE_VALUE {
            VALUE_NULL = -1, 
            VALUE_STRING = 0,
            VALUE_BOOL = 1,
            VALUE_NUMBER_D = 2,
            VALUE_NUMBER_I = 3,
            VALUE_OBJET = 4,
            VALUE_TABLE = 5
        };


        /**
         * @brief Value containing in a JSON file.
         */
        class Value {
            friend class _Objet;


        public:

            /**
             * @brief Construct a new Value object with null value
             *
             */
            Value();

            /**
             * @brief Construct a new Value object of type string
             *
             * @param valueString value in string
             */
            Value(std::string valueString);

            /**
             * @brief Construct a new Value object of type string
             *
             * @param valueString value in string
             */
            Value(const char* valueString);

            /**
             * @brief Construct a new Value object of type std::shared_ptr<_objet>
             *
             * @param std::shared_ptr<_objet> contains in the value
             */
            Value(std::shared_ptr<_Objet> pairs);

            /**
             * @brief Construct a new Value object of type number
             *
             * @param value in int
             */
            Value(int value);

            /**
             * @brief Construct a new Value object of type number
             *
             * @param value in double
             */
            Value(double value);

            /**
             * @brief Construct a new Value object of type bool
             *
             * @param value in bool
             */
            Value(bool value);

            /**
             * @brief Construct a new Value object of type bool
             *
             * @param value of table of value
             */
            Value(std::vector<Value> value);

#pragma region Accesseur

            /**
             * @return bool Indique si la valeur est null. Change the type of the value in VALUE_NULL.
             */
            bool isNull() const;

            /**
             * @brief Renvoie la valeur en boolean. Change the type of the value in VALUE_BOOL.
             *
             * @param _default Valeur par default si NULL ou type non convertible en boolean
             * @return bool Valeur en bool
             */
            bool asBool(bool _default = false);

            /**
             * @brief Renvoie la valeur en int. Change the type of the value in VALUE_NUMBER_I.
             *
             * @param _default Valeur par default si NULL ou type non convertible en int
             * @return int Valeur en int
             */
            int asInt(int _default = 0);

            /**
             * @brief Renvoie la valeur en double
             *
             * @param _default Valeur par default si NULL ou type non convertible en double. Change the type of the value in VALUE_NUMBER_D.
             * @return double Valeur en double
             */
            double asDouble(double _default = 0.0);

            /**
             * @brief Renvoie la valeur en char *. Change the type of the value in VALUE_STRING.
             *
             * @return char* Valeur en char *
             */
            const char* asString();

            /**
             * @brief Renvoie la valeur en std::shared_ptr<_objet>. Change the type of the value in VALUE_OBJET.
             *
             * @return std::shared_ptr<_Objet> Valeur en objet
             */
            std::shared_ptr<_Objet> asObjet();

            /**
             * @brief Renvoie la valeur en std::vector<Value>. Change the type of the value in VALUE_TABLE.
             *
             * @return std::vector<Value> Valeur en table
             */
            std::vector<Value> asTable();

            /**
             * @brief Get the type of value
             *
             * @param TYPE_VALUE Type of the value
             */
            TYPE_VALUE getType() const;

            operator const char* () { return this->asString(); };
            operator bool() { return this->asBool(); };
            operator double() { return this->asDouble(); };
            operator int() { return this->asInt(); };
            operator std::shared_ptr<_Objet>() { return this->asObjet(); };
            operator std::vector<Value>() { return this->asTable(); };
#pragma endregion

#pragma region Mutateur
            /**
             * @brief Set the value of the pair with NULL
             */
            void setNullValue();

            /**
             * @brief Set the value of the pair with a number
             *
             * @param newValue Nouvelle valeur en int
             */
            void setValue(int newValue);

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
            void setValue(const char* newValue);

            /**
             * @brief Set the value of the pair with a string
             *
             * @param newValue Nouvelle valeur en string
             */
            void setValue(std::string newValue);

            /**
             * @brief Set the value of the pair with a boolean
             *
             * @param newValue Nouvelle valeur en bool
             */
            void setValue(bool newValue);

            /**
             * @brief Set the value of the pair with a std::shared_ptr<_objet>
             *
             * @param newValue Nouvelle valeur en std::shared_ptr<_Objet>
             */
            void setValue(std::shared_ptr<_Objet> newValue);

            /**
             * @brief Set the value of the pair with a std::vector<Value>
             *
             * @param newValue Nouvelle valeur en std::vector<Value>
             */
            void setValue(std::vector<Value> newValue);

            void operator=(const char* value) { this->setValue(value); };
            void operator=(std::string value) { this->setValue(value); };
            void operator=(bool value) { this->setValue(value); };
            void operator=(double value) { this->setValue(value); };
            void operator=(int value) { this->setValue(value); };
            void operator=(std::shared_ptr<_Objet> value) { this->setValue(value); };
            void operator=(std::vector<Value> value) { this->setValue(value); };

#pragma endregion

            /**
             * @brief Ajoute une valeur dans le tableau de valeur
             *
             * @param value Valeur à ajouter
             */
            void append(Value value);

        protected:
            /**
             * @brief Type of the pair
             */
            TYPE_VALUE type = VALUE_NULL;

            /**
             * @brief Value in double
             */
            double valueDouble = 0;

            /**
             * @brief Value string of the pair
             */
            std::string valueString = "";

            /**
             * @brief std::shared_ptr<_Objet> containing by the pair
             */
            std::shared_ptr<_Objet> pairs = NULL;

            /**
             * @brief Value in table 
             */
            std::vector<Value>  valueTable;
        };
    }
}
#endif // __VALUE_H__