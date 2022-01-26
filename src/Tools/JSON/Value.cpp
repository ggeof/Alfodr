#include "Tools/JSON/Pair.h"
#include "Tools/JSON/Objet.h"

using namespace Alfodr::JSON;

Value::Value() :
    type(TYPE_VALUE::VALUE_NULL)
{
    
}

Alfodr::JSON::Value::Value(std::string _valueString) :
    type(TYPE_VALUE::VALUE_STRING), valueString(_valueString)
{
}

Value::Value(const char * _valueString) :
    type(TYPE_VALUE::VALUE_STRING), valueString(_valueString)
{
    
}

Value::Value(Objet _pairs) :
    type(TYPE_VALUE::VALUE_OBJET), pairs(_pairs)
{
    
}

Value::Value(int _value)  :
    type(TYPE_VALUE::VALUE_NUMBER_I), valueDouble(_value)
{
    
}

Value::Value(double _value)  :
    type(TYPE_VALUE::VALUE_NUMBER_D), valueDouble(_value)
{
    
}

Value::Value(bool _value) :
    type(TYPE_VALUE::VALUE_BOOL), valueDouble(_value)
{
    
}

Value::Value(std::vector<Value> value) :
    type(TYPE_VALUE::VALUE_TABLE), valueTable(value)
{

}

             

bool Value::isNull() const
{
    return type == VALUE_NULL;
}

bool Value::asBool(bool _default)
{
    if(type < VALUE_BOOL)
        this->setValue(_default);
    return bool(this->valueDouble);
}

int Value::asInt(int _default)
{
    if(type < VALUE_BOOL)
        this->setValue((double)_default);
    return int(this->valueDouble);
}

double Value::asDouble(double _default)
{
    if(type < VALUE_BOOL)
        this->setValue(_default);
    return double(this->valueDouble);   
}

const char * Value::asString()
{
    switch (this->type)
    {
        case TYPE_VALUE::VALUE_NULL:
            return "NULL";
        case TYPE_VALUE::VALUE_STRING:
            return valueString.c_str();
        case TYPE_VALUE::VALUE_BOOL:
            if(this->valueDouble == 1)
                return "True";
            else
                return "False";
        case TYPE_VALUE::VALUE_NUMBER_I :
            return std::to_string((int)this->valueDouble).c_str();
        case TYPE_VALUE::VALUE_NUMBER_D :
            return std::to_string((double)this->valueDouble).c_str();
        case TYPE_VALUE::VALUE_OBJET :
            return "Objet";
        case TYPE_VALUE::VALUE_TABLE:
            return "Table";
    }
    return "";
}

Objet Value::asObjet()
{
    if(type < VALUE_OBJET)
    {
        this->setValue(JSON::NewObjet());
    }
    return this->pairs; 
}

std::vector<Value> Alfodr::JSON::Value::asTable()
{
    if (type < VALUE_TABLE)
    {
        return std::vector<Value>();
    }
    return this->valueTable;
}

TYPE_VALUE Value::getType() const
{
    return this->type;
}

void Value::setValue(int newValue) 
{
    this->type = VALUE_NUMBER_I;
    this->valueDouble = newValue;
}

void Value::setValue(double newValue) 
{
    this->type = VALUE_NUMBER_D;
    this->valueDouble = newValue;
}

void Value::setValue(Objet newValue) 
{
    this->type = VALUE_OBJET;
    this->pairs = newValue;
}

void Value::setValue(bool newValue) 
{
    this->type = VALUE_BOOL;
    this->valueDouble = newValue;
}

void Alfodr::JSON::Value::setValue(std::vector<Value> newValue)
{
    this->type = VALUE_TABLE;
    this->valueTable = newValue;
}

void Alfodr::JSON::Value::append(Value value)
{
    if (this->type < VALUE_TABLE)
        this->type = VALUE_TABLE;
    this->valueTable.push_back(value);
}

void Value::setValue(const char * newValue) 
{
    this->type = VALUE_STRING;
    this->valueString = std::string(newValue);
}

void Value::setValue(std::string newValue) 
{
    this->type = VALUE_STRING;
    this->valueString = newValue;
}

void Value::setNullValue()
{
    this->type = VALUE_NULL;
}
