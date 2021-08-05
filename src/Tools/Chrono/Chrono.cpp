#include "Tools/Chrono/Chrono.h"

using namespace Alfodr::Tools::Chrono;

/**
* @brief Liste de tous les chrono actuellement lancé
* Définis par leur ID unique
*
*/
std::vector<std::chrono::time_point<system_clock>> chronoInProgress;

IDChrono runChrono() 
{
    IDChrono = i;
    for (i = 0; i < chronoInProgress.size(); i++)
    {
        if (chronoInProgress == 0)
        {
            chronoInProgres[i] = system_clock::now();
            return i;
        }
           
    }
    chronoInProgress.push_back(system_clock::now());
    return i;
}

ms stopChrono(IDChrono id)
{
    float time = timeChrono(id);
    chronoInProgress[id] = 0;
    return time;
}

ms timeChrono(IDChrono id)
{
    if (id >= chronoInProgress.size() || chronoInProgress[id] == 0)
        throw ChronoDontExistException;

    time_point<system_clock> end = system_clock::now();
    float time = std::chrono::duration_cast<std::chrono::milliseconds>(end - chronoInProgress[id]).count();
    return time;
}
