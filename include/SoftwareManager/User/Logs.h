#ifndef __LOGS_H__
#define __LOGS_H__

#include <fstream>
#include <ostream>

namespace Alfodr {
	namespace SoftwareManager {

        /**
         * Gére les logs de l'application, structure d'un message log : @b
         * Date & time :@b
         *      message@b
         * 
         * @warning chaque fichier log est supprimé au bout de T jours (si > 0)
         * 
         */
        template<int T>
		class Logs {
        public:
            /**
             * @brief Construct a new @ref Logs object
             *
             * @param path to the folder or file where the logs is written
             * @param writeInOnlyOneFile If true, the logs are writen in path, else are writen in folder path white the date like file name
             */
            Logs(const char * path, bool writeInOnlyOneFile = false);

            /**
             * @brief Destroy the @ref Logs object
            */
            ~Logs();

            /** Ecrire dans le fichier des logs un message
             * 
             * @param msg Message to be written
             */
            void writeLog(const char* msg);

            /** Ecrire dans le fichier des logs un message
             * 
             * @param msg Message to be written
             */
            void operator<<(const char* msg);

        protected:
            /**
                * @brief File of logs
                */
            std::ofstream fileLogs;
		};
	}
}


#endif // __LOGS_H__