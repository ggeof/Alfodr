#ifndef CHRONO_H
#define CHRONO_H

#include "../../Types/Types.h"

#include <chrono>
#include <vector>
#include <iostream>
#include <exception>

namespace Alfodr {


    namespace Tools {

        /**
         * @brief Représente l'ID d'un chrono lancé par la classe Logs
         *
         */
        typedef size_t IDChrono;

        class _Chrono {

            friend class Singleton<_Chrono>;

            public: 

                ~_Chrono();

                /**
                 * @brief Exception throw when the id of a chrono don't exist or it's stoped.
                 */
                class ChronoDontExistException : public std::exception
                {
                public :
                    ChronoDontExistException(IDChrono i) : id(i) {}

                    const char* what() const throw() { return ("The Chrono with ID : " + std::to_string(this->id) + " don't exists !").c_str(); }
                private:
                    IDChrono id;
                };

                /** Lance un chrono
                * @return l'ID du chrono lancé
                */
                IDChrono runChrono();

                /** Arrete un chrono
                * @param id ID du chrono a arreter
                * @return Temps mis par le chrono en milliseconde
                */
                ms stopChrono(IDChrono id);

                /** Demande le temps d'un chrono
                * @param id ID du chrono dont on veut connaitre le temps
                * @return Temps mis par le chrono en milliseconde
                */
                ms timeChrono(IDChrono id);

            protected:

                _Chrono(void * args) { };

            private:            

                /**
                * @brief Liste de tous les chrono actuellement lancé
                * Définis par leur ID unique
                *
                */
                std::vector<std::chrono::time_point<std::chrono::system_clock>> chronoInProgress;
        
        };

        /**
         * @brief Définition du singleton Chrono 
         */
        typedef Singleton<_Chrono> Chrono;
    }
}

#endif
