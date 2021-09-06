#include "Tools/Chrono/Chrono.h"

#include <mutex>

using namespace Alfodr;
using namespace Alfodr::Tools;

IDChrono _Chrono::runChrono() 
{
    static std::mutex m;
    
    m.lock();
    IDChrono i;
    for (i = 0; i < chronoInProgress.size(); i++)
    {
        if (chronoInProgress[i] == std::chrono::time_point<std::chrono::system_clock>())
        {
            chronoInProgress[i] = std::chrono::_V2::system_clock::now();
            m.unlock();
            return i;
        }
           
    }
    chronoInProgress.push_back(std::chrono::_V2::system_clock::now());
    m.unlock();

    return i;
}

ms _Chrono::stopChrono(IDChrono id)
{
    float time = timeChrono(id);
    chronoInProgress[id] = std::chrono::time_point<std::chrono::system_clock>();
    return time;
}

ms _Chrono::timeChrono(IDChrono id)
{
    if (id >= chronoInProgress.size() || chronoInProgress[id] == std::chrono::time_point<std::chrono::system_clock>())
        throw ChronoDontExistException(id);

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    float time = std::chrono::duration_cast<std::chrono::milliseconds>(end - chronoInProgress[id]).count();
    return time;
}

Alfodr::Tools::_Chrono::~_Chrono()
{
    chronoInProgress.clear();
}
