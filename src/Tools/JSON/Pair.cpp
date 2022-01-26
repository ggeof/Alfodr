#include "Tools/JSON/Pair.h"
#include "Tools/JSON/Objet.h"

using namespace Alfodr::JSON;

#include <stdio.h>
#include <string.h>

Alfodr::JSON::Pair::Pair(const char* _key, Value _value) :
    Value(_value)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key) :
    Value()
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, const char * _valueString) :
    Value(_valueString)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, Objet _pairs) :
    Value(_pairs)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, int _value)  :
    Value(_value)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, double _value)  :
    Value(_value)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, bool _value) :
    Value(_value)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char* _key, std::vector<Value> _table) :
    Value(_table)
{
    strcpy(this->key, _key);
}

const char * Pair::getKey() const
{
    return this->key;
}