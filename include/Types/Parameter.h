#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include "Types/Interval.h"

#include <exception>
#include <string>
#include <vector>


namespace Alfodr {

class Parameter
{
    friend class LstParameters;

    public:

        /**
         * @brief Nom du paramètre NULL
         * 
         */
        #define NAME_PARAM_NULL "NONE"

        /**
         * @brief Exception Lancé quand on souhaite un Paramètre dont le nom court est @ref NAME_PARAM_NULL : Impossible car c'est le paramètre null
         *
         */
        class NoParamCanBeNamedNONEException : public std::exception
        {
            public:
                virtual const char* what() const throw() { return "Class Parameter : No parameters can be named (short name) \"NONE\" ! "; }
        };

        /**
         * @brief Exception quand la modification d'un paramètre à échoué
         * 
         */
        class ExceptionModificationParameter : public std::exception
        {
            public:
                ExceptionModificationParameter(const char* _msg) : std::exception(), msg(_msg) {};

                virtual const char* what() const throw() { return msg; }

            private:
                const char* msg;
        };

        /**
         * @brief Type de valeur accepter par un parametre
         * 
         */
        enum TYPE_VALUE_PARAMETER {
            TV_INT      = 0,    /*!< Valeur entière >!*/
            TV_FLOAT    = 1,    /*!< Valeur flotante >!*/
            TV_ODD      = 2,    /*!< Valeur impaire >!*/
            TV_EVEN     = 3,    /*!< Valeur paire >!*/
            TV_BOOL     = 4     /*!< Valeur booleen >!*/
        };

        /**
         * @brief Comment un paramètre peut-être modifié
         *
         */
        enum TYPE_MODIFICATION_PARAMETER {
            TM_IMPOSSIBLE = 0,          /*!< On ne peut modifier le paramètre >!*/
            TM_POSSIBLE = 1,            /*!< Modification Possible >!*/
            TM_NO_INTERFACE = 2,        /*!< Pas de modification possible dans l'interface >!*/
            TM_ONLY_PROGRAMMER = 3,     /*!< Seulement pour le programmeur >!*/
        };

    public:

        /**
        * @brief Construct a new @ref Parameter object
        *
        * @param shortName Nom court
        * @param longName Nom long
        * @param value Valeur du parametre
        * @param interval Interval des valeurs autorisé
        * @param type Type de valeur accepter pour le parametre
        * @param modificationParametre Indique comment on peut modifier le paramètre
        */
        Parameter(  std::string shortName,
                    std::string longName,
                    float value,
                    Interval<float> interval,
                    TYPE_VALUE_PARAMETER type = TYPE_VALUE_PARAMETER::TV_FLOAT,
                    TYPE_MODIFICATION_PARAMETER modificationParametre = TM_POSSIBLE);

        /**
        * @brief Construct a new @ref Parameter object by copie
        *
        * @param param Parametre à copier
        * @param shortName Nom court du nouveau parametre
        * @param longName Nom long du nouveau parametre
        */
        Parameter(  Parameter param,
                    std::string shortName,
                    std::string longName);

        /**
        * @brief Destroy the @ref Parameter object
        *
        */
        ~Parameter();


        #pragma region Accesseur
                /** @brief Get the Long Name object
                *   @return std::string Nom long du parametre
                */
                inline std::string getLongName() const { return this->longName; }

                /** @brief Get the Short Name object
                *   @return std::string Nom court du parametre
                */
                inline std::string getShortName() const { return this->shortName; }

                /** @brief Get the Type Modification object
                 *  @return TYPE_MODIFICATION_PARAMETER Type de modification sur le paramètre
                 */
                inline TYPE_MODIFICATION_PARAMETER getTypeModification() const { return this->typeModification; }
                
                /** @brief Get the Value object
                *   @return float Valeur du parametre
                */
                inline float getValue() const { return this->value; }


                /** @brief Get the Value in float of the parameter
                *   @return float Valeur du parametre
                */
                inline operator float() const { return (float)this->value;  }

                /** @brief Get the Value in bool of the parameter
                *   @return bool Valeur du parametre
                */
                inline operator bool() const { return (bool)this->value; }

                /** @brief Get the Value in int of the parameter
                *   @return int Valeur du parametre
                */
                inline operator int() const { return (int)this->value; }

                /** @brief Get the Type Value object
                * @return TYPE_VALUE_PARAMETER Type de valeur du parametre
                */
                inline TYPE_VALUE_PARAMETER getTypeValue() const { return this->typeValue; }

        #pragma endregion

        #pragma region Mutateur
                /** @brief Set the Max object
                * @param _max Nouvelle valeur max du parametre
                */
                inline void setMax(float _max) { this->interval.increaseTo(_max); 
	                if(this->interval.isOut(this->value)) this->value = _max;
                }

                /** @brief Set the Min object
                * @param _min Nouvelle valeur min du parametre
                */
                inline void setMin(float _min) { this->interval.decreaseTo(_min); 
	                if(this->interval.isOut(this->value)) this->value = _min;
                }

                /**
                 * @brief Set the @ref interval object
                 * @param _interval new interval for the parameter
                 */
                inline void setInterval(Interval<float> _interval) {
                    this->interval = _interval;
	                if(this->interval.getMin() > this->value) this->value = this->interval.getMin();
	                if(this->interval.getMax() < this->value) this->value = this->interval.getMax();
                    
                }

                /**
                * @brief Set the Value object
                * @param value Nouvelle valeur du parametre
                * @warning Peut provoquer une erreur de type string si value n'est pas bon
                */
                void setValue(float value);

                
                Parameter &operator=(const float & f) { this->setValue(f); return *this;};
                Parameter &operator=(const Parameter & p) {
                    this->interval = p.interval;
                    this->setValue(p.getValue());
                    return *this;
                };
        #pragma endregion

    protected:

        /**
        * @brief Construct a null parameter
        *
        */
        Parameter();

        /**
        * @brief Nom court pour le parametre (utiliser dans le programme)
        */
        std::string shortName;

        /**
        * @brief Nom long pour le parametre (à afficher pour l'utilisateur)
        */
        std::string longName;

        /**
        * @brief Type de valeur pour le parametre
        */
        TYPE_VALUE_PARAMETER typeValue;

        /**
        * @brief Valeur du parametre
        */
        float value;

        /**
         * @brief Interval of autorized values 
         */
        Interval<float> interval;

        /**
         * @brief comment le paraètre peut être modifié
         */
        TYPE_MODIFICATION_PARAMETER typeModification;

};

class LstParameters
{
    public:
        /**
         * @brief Exception quand on demande dans une liste de paramètre, un paramètre qui n'existe pas
         * 
         */
        class NoParamToThisNameException : public std::exception
        {
        public:
            NoParamToThisNameException(std::string _nameParameter) : nameParameter(_nameParameter) {}

            virtual const char* what() const throw()
            {
                return ("Class LstParameters : No parameters for this name : " + nameParameter).c_str();
            }

        private:
            /**
             * @brief Nom du paramètre que nous avons essayer de chercher
             * 
             */
            std::string nameParameter;
        };

        /**
         * @brief Construct a new Lst Parameters object
         * 
         */
        LstParameters();

        /**
         * @brief Construct a new Lst Parameters object by copie
         * 
         * @param otherListe Liste à copier
         */
        LstParameters(const LstParameters& otherListe);
        
        /**
         * @brief Construct a new Lst Parameters object
         * 
         * @param _size Taille à réserver
         */
        LstParameters(size_t _size);

        /**
         * @brief Destroy the Lst Parameters object
         * 
         */
        ~LstParameters();


        /**
         * @brief Iterator pour @ref LstParameters
         * 
         */
        class iterator : public std::vector<Parameter>::const_iterator
        {
            public:
                /**
                 * @brief Construct a new iterator object
                 * 
                 * @param it std::vector::iterator
                 * @param _sizeListe Taille de la liste
                 * @param _id id de l'iterator
                 */
                iterator(std::vector<Parameter>::const_iterator it, size_t _sizeListe, int _id);

                /**
                 * @brief Passe à l'élément suivant
                 * 
                 * @return iterator Iterator suivant
                 */
                iterator operator++();

                /**
                 * @brief Passe à l'élément suivant
                 * 
                 * @return iterator Iterator suivant
                 */
                iterator operator++(int);

                /**
                 * @brief Compare l'iterator avec un autre
                 * 
                 * @param i Iterator à comparer
                 * @return true Les itérators ne sont pas égaux
                 * @return false Les itérators sont égaux
                 */
                bool operator!=(const iterator i);


            private:

                /**
                 * @brief Taille de la liste
                 * 
                 */
                size_t sizeListe;

                /**
                 * @brief ID de l'iterator
                 * 
                 */
                int id;
        };

        /**
         * @brief Premier paramètre
         * 
         * @return LstParameters::iterator Paramètre 
         */
        LstParameters::iterator begin() const;

        /**
         * @brief Fin de la liste
         * 
         * @return LstParameters::iterator Paramètre Final (Paramètre NULL) 
         */
        LstParameters::iterator end() const;

        /**
         * @brief Insert un paramètre dans la liste
         * 
         * @param newParameter Paramètre à insérer
         */
        void insert(Parameter newParameter);

        /**
         * @brief Retire un paramètre
         * 
         * @param name Nom du paramètre à enlever
         */
        void remove(char* name);

        /**
         * @brief Efface les éléments de la liste
         * 
         */
        void clear();

        /**
         * @brief Récupère un paramètre avec son nom
         * 
         * @param name Nom du paramètre
         * @return Parameter& Paramètre 
         * 
         * @warning Exception : @ref NoParamToThisNameException
         */
        Parameter& at(const char* name);

        /**
         * @brief Récupère un paramètre avec son nom
         * 
         * @param name Nom du paramètre
         * @return Parameter& Paramètre 
         * 
         * @warning Exception : @ref NoParamToThisNameException
         */
        inline Parameter& operator[](const char* name) { return this->at(name); }

        LstParameters& operator=(LstParameters otherLst);

        /**
         * @return size_t Taille de la liste
         */
        size_t size() const;

        /**
         * @brief Indique si la liste est vide
         * 
         * @return true La liste est vide
         * @return false La liste n'est pas vide
         */
        bool empty() const;

        /**
         * @brief Get the Name Of All Parameters object
         * 
         * @return std::vector<std::string> Liste des noms de tout les paramètres enregistrés
         */
        std::vector<std::string> getNameOfAllParameters() const;

        /**
         * @brief Réserve de l'espace 
         * 
         * @param s Taille à réserver
         */
        void reserve(size_t s);

        /**
         * @brief Modifie la taille du container
         * 
         * @param s Nouvelle taille max
         * @warning Des éléments peuvent disparaitre si la nouvelle taille max est 4 fois plus petite que le nombre d'élément 
         */
        void resize(size_t s);

    private:

        /**
         * @brief Vecteur contenant tout les paramètres
         */
        std::vector<Parameter> parameters;

        /**
         * @brief Taille de la liste
         */
        size_t s;

        /**
         * @brief Nombre maximum d'élément dans la liste
         */
        size_t sizeMax;

        /**
         * @brief Fonction de hachage
         * 
         * @param name à hacher
         * @return size_t Position dans @ref parameters
         */
        inline size_t hachageFct(std::string name) const;

        /**
         * @brief Nombre de sous niveau
         * 
         */
        const size_t SUB_LEVEL = 4;
};


}
#endif // __PARAMETER_H__