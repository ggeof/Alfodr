#include "Tools/JSON/Pair.h"

using namespace Alfodr::JSON;


Pair::Pair(const char * _key) :
    key(_key), type(TYPE_PAIR::PAIR_NULL)
{
    
}

Pair::Pair(const char * _key, char * _valueString) :
    key(_key), type(TYPE_PAIR::PAIR_STRING), valueString(_valueString)
{
    
}

Pair::Pair(const char * _key, Objet _pairs) :
    key(_key), type(TYPE_PAIR::PAIR_OBJET), pairs(_pairs)
{
    
}

Pair::Pair(const char * _key, double _value)  :
    key(_key), type(TYPE_PAIR::PAIR_NUMBER), valueDouble(_value)
{
    
}

Pair::Pair(const char * _key, bool _value) :
    key(_key), type(TYPE_PAIR::PAIR_BOOL), valueDouble(_value)
{

}

const char * Pair::getKey() const
{
    return this->key;
}
             

bool Pair::isNull() const
{
    return type == PAIR_NULL;
}

bool Pair::asBool(bool _default) const
{
    if(type < PAIR_BOOL)
        return _default;
    return bool(this->valueDouble);
}

int Pair::asInt(int _default) const
{
    if(type < PAIR_BOOL)
        return _default;
    return int(this->valueDouble);
}

double Pair::asDouble(double _default) const
{
    if(type < PAIR_BOOL)
        return _default;
    return double(this->valueDouble);   
}

char * Pair::asString() const
{
    if(type < PAIR_STRING)
        return "null";
    return this->valueString;
}

Objet Pair::asObjet(Objet _default) const
{
    if(type < PAIR_OBJET)
    {
        if(_default == NULL)
            return _Objet::newObjet();
        else
            return _default;
    }
    return this->pairs;
}

TYPE_PAIR Pair::getType() const
{
    return this->type;
}

void Pair::setValue(double newValue) 
{
    this->type = PAIR_NUMBER;
    this->valueDouble = newValue;
}

void Pair::setValue(Objet newValue) 
{
    this->type = PAIR_OBJET;
    this->pairs = newValue;
}

void Pair::setValue(bool newValue) 
{
    this->type = PAIR_BOOL;
    this->valueDouble = newValue;
}

void Pair::setValue(char * newValue) 
{
    this->type = PAIR_STRING;
    this->valueString = newValue;
}

void Pair::setValueNULL() 
{
    this->type = PAIR_NULL;
}
