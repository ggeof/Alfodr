#ifndef __SETUP_H__
#define __SETUP_H__

#include "Tools/JSON/JSONFile.h"

namespace Alfodr {
	namespace SoftwareManager {
		class Setup {
		public:
			
			/**
			 * @brief Construct a new Setup object
			 * 
			 * @param fileConfig Fichier de configuration actuel	
			 * @param fileDefault Fichier par default
			 */
			Setup(const char* fileConfig, const char* fileDefault = "");

			~Setup();

			/**
			 * @brief R�cup�re une collection de param�tre
			 *
			 * @param nameParamters nom de la collection
			 * @return JSON::Objet Collection de param�tre
			 */
			JSON::Objet getCollectionParameters(const char* nameCollection);

			/**
			 * @brief R�cup�re les param�tres gr�ce � son nom
			 *
			 * @param nameParamters nom du param�tre
			 * @return std::shared_ptr<JSON::Pair> Pointeur vers la Pair li� au param�tre
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