#include "Tools/JSON/Objet.h"

#include <string>

using namespace Alfodr::JSON;

_Objet::~_Objet() 
{
    this->pairs.clear();
}
        

void _Objet::insertPair(std::shared_ptr<Pair> pair) 
{
    std::string str(pair->getKey());
    size_t i; 

    for(i = 0; i < pairs.size(); i++)
    {
        if(std::string(pairs[i]->getKey()) == str )
            throw PairWithKeyAlreadyExistException(str.c_str());
    }

    pairs.push_back(pair);
}

void _Objet::removePair(const char * keyPair) 
{
    std::string str(keyPair);

    for(size_t i = 0; i < pairs.size(); i++)
    {
        if(std::string(pairs[i]->getKey()) == str )
        {
            pairs.erase(pairs.begin() + i);
            return;
        }
    }

    throw PairDontExistException(keyPair);
    
}

std::shared_ptr<Pair> Alfodr::JSON::_Objet::getPair(const char* keyPair)
{
    std::string str(keyPair);
    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (std::string(pairs[i]->getKey()) == str)
            return pairs[i];
    }

    std::shared_ptr<Pair> newPair = std::make_shared<Pair>(keyPair);
    this->insertPair(newPair);
    return newPair;
}

_Objet::_Objet()
{

}


std::shared_ptr<Pair> _Objet::operator[](const char * keyPair)
{
    return this->getPair(keyPair);
}

std::vector<std::shared_ptr<Pair>> _Objet::getPairs() 
{
    return this->pairs;
}

std::shared_ptr<_Objet> Alfodr::JSON::NewObjet()
{
    auto o = new _Objet();
    return std::shared_ptr<_Objet>(o);
}
