#include "SoftwareManager/User/Logs.h"

#include <experimental/filesystem>
#include <iostream>


using namespace std::chrono;

template<int T>
Alfodr::SoftwareManager::Logs<T>::Logs(const char* path, bool writeInOnlyOneFile)
{
    if (writeInOnlyOneFile)
    {
        this->fileLogs = std::ofstream(path);
    }
    else
	{
        // On purge les fichiers si besoin
        const auto now = std::experimental::filesystem::file_time_type::clock::now();
        if(T > 0)
            for (auto& p : std::experimental::filesystem::directory_iterator(path))
            {
                if (duration_cast<hours>(now - std::experimental::filesystem::last_write_time(p)).count() > 24 * T)   // Si nbHours est supérieur à 24h * T jours => un moi
                    std::experimental::filesystem::remove(p);                          // On supprime

            }

        std::time_t end_time = system_clock::to_time_t(system_clock::now());
        this->fileLogs = std::ofstream(std::string(path) + std::string(std::ctime(&end_time)) + ".log");
	}


}

template<int T>
Alfodr::SoftwareManager::Logs<T>::~Logs()
{
    this->fileLogs.close();
}

template<int T>
void Alfodr::SoftwareManager::Logs<T>::writeLog(const char* text)
{
    std::time_t end_time = system_clock::to_time_t(system_clock::now());
    std::string nwText = std::string(std::ctime(&end_time));
    nwText.pop_back();
    nwText += " : \n\t";
    nwText += text;
    nwText += "\n";

    if (this->fileLogs.is_open())
    {
        /**
         * Format :
         *
         * Date :
         *      Text de log
         */
        this->fileLogs.write(nwText.c_str(), nwText.size());
        this->fileLogs.flush(); // On synchronise
    }
    else
        std::cerr << nwText;
}

template<int T>
void Alfodr::SoftwareManager::Logs<T>::operator<<(const char* text)
{
    this->writeLog(text);
}
