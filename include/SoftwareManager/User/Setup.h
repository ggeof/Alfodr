#ifndef __SETUP_H__
#define __SETUP_H__

#include "Tools/JSON/JSONFile.h"

namespace Alfodr {
	namespace SoftwareManager {
		class Setup {
		public:
			
			Setup(const char* fileConfig, const char* fileDefault);

			~Setup();

			/**
			 * @brief Récupère une collection de paramètre
			 *
			 * @param nameParamters nom de la collection
			 * @return JSON::Objet Collection de paramètre
			 */
			JSON::Objet getCollectionParameters(const char* nameCollection);

			/**
			 * @brief Récupère les paramètres grâce à son nom
			 *
			 * @param nameParamters nom du paramètre
			 * @return std::shared_ptr<JSON::Pair> Pointeur vers la Pair lié au paramètre
			 */
			std::shared_ptr<JSON::Pair> getParameters(const char* nameParamters);

			/**
			 * @brief Save the configuration.
			 */
			void save();

			/**
			 * @brief Reload the values default of the parameters.
			 */
			void reloadDefault();


			/**
			 * @brief Remplace le fichier de dafault de configuration par le fichier actuel
			 */
			void setConfigurationInDefault();

		private:

			/**
			 * @brief Config JSOn
			 *
			 */
			JSON::Objet root;

			/**
			 * @brief name of the parameter/configuration save file
			 *
			 */
			const char * fileConfig;

			/**
			 * @brief name file of the file json by default
			 *
			 */
			const char* fileConfigDefault;
			
		};
	}
}

#endif // __SETUP_H__