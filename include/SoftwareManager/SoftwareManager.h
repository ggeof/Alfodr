#ifndef SOFTWARE_MANAGER
#define SOFTWARE_MANAGER

#include "ArgumentReader.h"
#include "User/User.h"
#include "Types/Types.h"

namespace Alfodr {

	namespace SoftwareManager
	{
		void initSoftwareAlfodr(const char* softwareName);

		/**
		 * @brief Name of the application.
		 */
		static const char* SOFTWARE_NAME = nullptr;

		/**
		 * @brief Chemin vers le dosier contenant les ressources de l'application
		 */
		static const char* FOLDER_RESSOURCE_APPLICATIONS = nullptr;

		/**
		 * @brief Chemin vers le dosier contenant les ressources de l'application relatif � l'utilisateur .
		 */
		static const char* FOLDER_USER_APPLICATIONS = nullptr;
	}
}


#endif
