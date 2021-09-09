#ifndef SOFTWARE_MANAGER
#define SOFTWARE_MANAGER

#include "User/User.h"
#include "Types/Types.h"

namespace Alfodr {

	namespace SoftwareManager
	{
		void initSoftwareAlfodr(const char* softwareName);

		/**
		 * @brief Name of the application.
		 */
		static const char* SOFTWARE_NAME;

		/**
		 * @brief Chemin vers le dosier contenant les ressources de l'application relatif à l'utilisateur .
		 */
		static const char* FOLDER_USER_APPLICATIONS;
	}
}


#endif
