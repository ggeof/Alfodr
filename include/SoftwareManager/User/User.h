#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <exception>
#include <map>

#include "SoftwareManager/SoftwareManager.h"

#include "Tools/Tools.h"

#include "Logs.h"
#include "Setup.h"

namespace Alfodr {
	namespace SoftwareManager {
		/**
		 * @brief Niveau de compte utilisateur
		 * 
		*/
		enum LevelUser {
			UT,             /*!< Unit Test >*/
			OPERATOR,       /*!< Operator Machine >*/
			ADMINISTRATOR,  /*!< Administrator >*/
			DEVELOPPER,     /*!< Developper>*/
			GOD             /*!< God, but it's never used... >*/
		};



        /**
         * @brief class gérant le niveau de l'utisateur dans l'application.
         */
		class _User : public Logs<31>, public Setup {
        
            friend class Singleton<_User>;

        public:

            /**
             * @brief Exception throw when the software name is not initialized
             */
            class NameOfSoftwareNotInitialized : public std::exception
            {
            public:
                const char* what() const throw() { return "The name of application is not initialized !"; } 
            };

            /**
             * @brief Exception throw when the password for a level is not defined
             */
            class PasswordOfUserNotDefined : public std::exception
            {
            public:
                PasswordOfUserNotDefined(LevelUser level) {
                    switch (level)
                    {
                    case Alfodr::SoftwareManager::UT: levelUser = "UT";  break;
                    case Alfodr::SoftwareManager::OPERATOR: levelUser = "OPERATOR";break;
                    case Alfodr::SoftwareManager::ADMINISTRATOR: levelUser = "ADMINISTRATOR";break;
                    case Alfodr::SoftwareManager::DEVELOPPER: levelUser = "DEVELOPPER";break;
                    case Alfodr::SoftwareManager::GOD: levelUser = "GOD";break;
                    default: levelUser = "";break;
                    }
                }

                const char* what() const throw() { return ("The password for the user level : " + std::string(levelUser) + " is not defined !").c_str(); }
            private:
                const char * levelUser;
            };

            /**
             * @brief Destroy the @ref User object
             *
             */
            ~_User();

            /**
             * @brief Change the level of user
             *
             * @warning the exception @ref PasswordOfUserNotDefined can be invoked
             * 
             * @param user 
             * @param password the password who determines the level of user
             * @return true the password is valid
             * @return false the password is not valid
             */
            bool loging(LevelUser user, char * password);

            /** Ecrire dans le fichier des logs un message. If the @ref levelUser is > of Administrator or start whith "*", the message is written in console.
            *
             * @param text string du message a afficher
             */
            void writeLog(const char* msg);

            /** Ecrire dans le fichier des logs un message. If the @ref levelUser is > of Administrator or start whith "*", the message is written in console.
             *
             * @param msg Message to be written
             */
            void operator<<(const char* msg);

            /**
             * @brief Set the password for different level of user.
             * If the level  actually is >= of a level who the password is modified, the type user is set to OPERATOR.
             *
             * @param nbPasswordSet Nombre de couple (level, password) à mettre à jour
             * @param ... enchainement de (dans l'ordre) TypeUser et de char*
             */
            void setPassword(size_t nbPasswordSet, ...);

    #pragma region Acesseurs
                /**      
                * @return Return the level of user
                */
                LevelUser getLevelUser() { return this->levelUser; }
    #pragma endregion



        protected:

            /**
             * @brief Construc the @ref User object, with LevelUser OPERATOR
             *
             */
            _User();

            /**
             * @brief Level of the user. Defined the permissions in application
             */
            LevelUser levelUser;

			
        private:
            /**
             * @brief password for change the user level.
             */
            std::map<LevelUser, char*> passwords;
		};

		/**
		 * @brief D�finition du singleton User
		 */
		typedef Singleton<_User> User;
	}
}

#endif // __USER_H__