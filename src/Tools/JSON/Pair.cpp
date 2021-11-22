#include "Tools/JSON/Pair.h"
#include "Tools/JSON/Objet.h"

using namespace Alfodr::JSON;

#include <stdio.h>
#include <string.h>

Pair::Pair(const char * _key) :
    type(TYPE_PAIR::PAIR_NULL)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, char * _valueString) :
    type(TYPE_PAIR::PAIR_STRING), valueString(_valueString)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, Objet _pairs) :
    type(TYPE_PAIR::PAIR_OBJET), pairs(_pairs)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, int _value)  :
    type(TYPE_PAIR::PAIR_NUMBER_I), valueDouble(_value)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, double _value)  :
    type(TYPE_PAIR::PAIR_NUMBER_D), valueDouble(_value)
{
    strcpy(this->key, _key);
}

Pair::Pair(const char * _key, bool _value) :
    type(TYPE_PAIR::PAIR_BOOL), valueDouble(_value)
{
    strcpy(this->key, _key);
}

const char * Pair::getKey() const
{
    return this->key;
}
             

bool Pair::isNull() const
{
    return type == PAIR_NULL;
}

bool Pair::asBool(bool _default)
{
    if(type < PAIR_BOOL)
        this->setValue(_default);
    return bool(this->valueDouble);
}

int Pair::asInt(int _default)
{
    if(type < PAIR_BOOL)
        this->setValue((double)_default);
    return int(this->valueDouble);
}

double Pair::asDouble(double _default)
{
    if(type < PAIR_BOOL)
        this->setValue(_default);
    return double(this->valueDouble);   
}

#include <string>

const char * Pair::asString()
{
    switch (this->type)
    {
        case TYPE_PAIR::PAIR_NULL:
            return "NULL";
        case TYPE_PAIR::PAIR_STRING:
            return valueString;
        case TYPE_PAIR::PAIR_BOOL:
            if(this->valueDouble == 1)
                return "True";
            else
                return "False";
        case TYPE_PAIR::PAIR_NUMBER_I :
            return std::to_string((int)this->valueDouble).c_str();
        case TYPE_PAIR::PAIR_NUMBER_D :
            return std::to_string((double)this->valueDouble).c_str();
        case TYPE_PAIR::PAIR_OBJET :
            return "Objet";
    }
    return "";
}

Objet Pair::asObjet()
{
    if(type < PAIR_OBJET)
    {
        this->setValue(JSON::NewObjet());
    }
    return this->pairs; 
}

TYPE_PAIR Pair::getType() const
{
    return this->type;
}

void Pair::setValue(int newValue) 
{
    this->type = PAIR_NUMBER_I;
    this->valueDouble = newValue;
}

void Pair::setValue(double newValue) 
{
    this->type = PAIR_NUMBER_D;
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
