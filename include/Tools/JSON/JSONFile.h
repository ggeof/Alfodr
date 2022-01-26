#ifndef __JSONFILE_H__
#define __JSONFILE_H__

#include "Objet.h"

namespace Alfodr {
    namespace JSON {

        /**
         * @brief Exception throw when the reading of a json file as failed
         */
        class ERRORReadJSONFileException : public std::exception
        {
        public :
            const char* what() const throw() { return "ERROR : the reading of json file as failled !"; }

        };

        /**
         * @brief Open a JSON file and return this structure
         * 
         * @warning the exception @ref ERRORReadJSONFileException can be throw 
         * 
         * @param path to the file
         * @return Objet Structure of the JSON file
         */
        Objet openJSONFile(const char * path);

        /**
         * @brief Write a JSON file with this structure
         * 
         * @param path of the file
         * @param objet saved
         * @return Objet Structure of the JSON file
         */
        void writeJSONFile(const char * path, Objet objet);
    }
}
#endif // __JSONFILE_H__