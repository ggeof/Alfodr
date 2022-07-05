#ifndef __OBJET_H__
#define __OBJET_H__

#include <memory>
#include <exception>
#include <string>
#include <vector>


#include "Pair.h"


namespace Alfodr {

    namespace JSON {

        class Pair;
        class _Objet;

        /**
         * @brief A objet is a pointer to _Objet
         * 
         */
        typedef std::shared_ptr<_Objet> Objet;

        /**
         * @brief Class objet qui ne peut pas être initialisé car un objet ne peut être un pointeur de type std::shared_ptr
         * 
         */
        class _Objet
        {
            friend std::shared_ptr<_Objet> NewObjet();
            
            /**
             * @brief Exception throw when the pair with a key already exist in the objet 
             */
            class PairWithKeyAlreadyExistException : public std::exception
            {
            public :
                PairWithKeyAlreadyExistException(const char * _key) : key(_key) {}

                const char* what() const throw() { return ("The Pair with key : " + std::string(this->key) + " already exists !").c_str(); }
            private:
                const char * key;
            };

            /**
             * @brief Exception throw when the pair with a key don't exist in the objet 
             */
            class PairDontExistException : public std::exception
            {
            public :
                PairDontExistException(const char * _key) : key(_key) {}

                const char* what() const throw() { return ("The Chrono with ID : " + std::string(this->key) + " don't exists !").c_str(); }
            private:
                const char * key;
            };

            

            public :

                /**
                 * @brief Destroy the objet object
                 * 
                 */
                ~_Objet();

                /**
                 * @brief Insert a new pair in the objet
                 * 
                 * @warning can be return exception : @ref PairWithKeyAlreadyExistException
                 * 
                 * @param pair new pair who must to be insered
                 */
                void insertPair(Pair pair);

                /**
                 * @brief Insert a new pair in the objet
                 * 
                 * @warning can be return exception : @ref PairWithKeyAlreadyExistException
                 * 
                 * @param pair new pair who must to be insered
                 */
                void insertPair(std::shared_ptr<Pair> pair);

                
                /**
                 * @brief Remove a pair in the objet
                 * 
                 * @warning can be return exception : @ref PairDontExistException
                 * 
                 * @param keyPair key of pair who must to be removed
                 */
                void removePair(const char * keyPair);

                /**
                 * @brief Inidcate if a pair exist in the objet
                 * 
                 * @param keyPair key of the pair
                 * @return true the pair exist
                 * @return false the pair don't exist
                 */
                bool pairExist(const char* keyPair);

                /**
                 * @brief get pair with specific key, if pair don't exist a pair is created
                 *                  
                 * @param keyPair key of the pair
                 * @return std::shared_ptr<Pair> pair returned
                 */
                std::shared_ptr<Pair> getPair(const char* keyPair);

                /**
                 * @brief get pair with specific key
                 *                  
                 * @param keyPair key of the pair
                 * @return std::shared_ptr<Pair> pair returned
                 */
                std::shared_ptr<Pair> operator[](const char * keyPair);

                /**
                 * @brief Get the Pairs object
                 * 
                 * @return std::vector<std::shared_ptr<Pair>> Liste de toute les pairs de l'objet
                 */
                std::vector<std::shared_ptr<Pair>> getPairs();

            protected :

                /**
                 * @brief Construct a new objet object
                 */
                _Objet();

                /**
                 * @brief Liste de toute les pairs contenu dans l'objet
                 * 
                 */
                std::vector<std::shared_ptr<Pair>> pairs;

        };
        
        std::shared_ptr<_Objet> NewObjet();

    }


}

#endif // __OBJET_H__