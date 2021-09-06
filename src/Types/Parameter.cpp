#include "Types/Parameter.h"

#include <numeric>

using namespace Alfodr;

Parameter::Parameter() :
	shortName(NAME_PARAM_NULL), longName(NAME_PARAM_NULL), typeValue(TV_INT), value(0),interval({0,0}), typeModification(TM_IMPOSSIBLE)
{

}

Parameter::Parameter(std::string _shortName,
					std::string _longName,
					float _value,
					Interval<float> _interval,
					TYPE_VALUE_PARAMETER _type,
                    TYPE_MODIFICATION_PARAMETER _typeModification) :
	shortName(_shortName), longName(_longName), typeValue(_type), interval(_interval), typeModification(_typeModification)
{
	if (_shortName == NAME_PARAM_NULL)
		throw NoParamCanBeNamedNONEException();

	if(_type == TV_BOOL)
	{
		this->interval = {0,1};
	}

	setValue(_value);
}

Parameter::Parameter(Parameter param,
					std::string _shortName,
					std::string _longName) :
	Parameter(param)
{
	shortName = _shortName;
	longName = _longName;
}

Parameter::~Parameter() 
{
	
}

void Parameter::setValue(float _value) 
{
	if(this->typeModification == TYPE_MODIFICATION_PARAMETER::TM_IMPOSSIBLE)
		throw ExceptionModificationParameter(("ERROR "+ this->longName + " can't be modifiate ! ").c_str());

    if(this->interval.isOut(_value))
		throw ExceptionModificationParameter(("ERROR with value " + std::to_string(_value) + " : " + this->longName + " must be between " + std::to_string(this->interval.getMin()) + " and " + std::to_string(this->interval.getMax()) + " ! ").c_str());

    switch (this->typeValue)
    {
        case TYPE_VALUE_PARAMETER::TV_INT :
            this->value = (int) _value;
            break;
        case TYPE_VALUE_PARAMETER::TV_ODD :
            if((int) _value % 2 == 1)
                this->value = (int) _value;
			else
				throw ExceptionModificationParameter(("ERROR with value " + std::to_string(_value) + " : " + this->longName + " must be odd ! ").c_str());
            break;
        case TYPE_VALUE_PARAMETER::TV_EVEN :
            if((int) _value % 2 == 0)
                this->value = (int) _value;
			else
				throw ExceptionModificationParameter(("ERROR with value " + std::to_string(_value) + " : " + this->longName + " must be ever ! ").c_str());
            break;

        case TYPE_VALUE_PARAMETER::TV_BOOL :
			this->value = (bool) _value;
            break;

        default:
            this->value = _value;
            break;
    }    
}


LstParameters::LstParameters() : s(0), sizeMax(0)
{
    this->reserve(1);
}

LstParameters::LstParameters(const LstParameters& otherListe)
    : s(0), sizeMax(0)
{
    this->reserve(otherListe.sizeMax);

    for (size_t i = 0; i < otherListe.parameters.size(); i++)
    {
        if (otherListe.parameters[i].getShortName() != NAME_PARAM_NULL)
            this->insert(otherListe.parameters[i]);
    }
}

LstParameters::LstParameters(size_t _size) : s(0), sizeMax(0)
{
    this->reserve(_size);
}

LstParameters::~LstParameters()
{
    this->clear();
}

LstParameters::iterator LstParameters::begin() const
{
    std::vector<Parameter>::const_iterator begin = this->parameters.begin();
    int id = 0;
    while (begin != this->parameters.end() && begin->getShortName() == NAME_PARAM_NULL)
    {
        begin++;
        id++;
    }    

    return LstParameters::iterator(begin, this->parameters.size(), id);
}

LstParameters::iterator LstParameters::end() const
{
    return LstParameters::iterator(this->parameters.end(), this->parameters.size(),-1);
}

void LstParameters::insert(Parameter newParameter)
{
    if(this->s == this->sizeMax)
        this->resize(this->sizeMax * 2);

    size_t id = this->hachageFct(newParameter.getShortName());

    size_t id2 = id;
    do
    {

        if (this->parameters[id2].getShortName() == NAME_PARAM_NULL)
        {
            this->parameters[id2] = newParameter;
            this->s++;
            return;
        }
        id2++;
        if (id2 >= this->parameters.size())
            id2 = 0;
    } while(id2 != id);
}

void LstParameters::remove(char* name)
{
    for (size_t i = 0; i < this->parameters.size(); i++)
    {
        if (this->parameters[i].getShortName() == std::string(name))
        {
            this->parameters[i] = Parameter();
            this->s--;
            return;
        }
    }
}

void LstParameters::clear()
{
    this->s = 0;
    this->parameters.clear();
    for (size_t i = 0; i < this->sizeMax * SUB_LEVEL; i++)
    {
        this->parameters.push_back(Parameter());
    }
}

Parameter& LstParameters::at(const char* name)
{
    size_t id = this->hachageFct(name);

    size_t id2 = id;
    do
    {
        if (this->parameters[id2].getShortName() == std::string(name))
        {
            return this->parameters[id2];
        }
        id2++;
        if (id2 >= this->parameters.size())
            id2 = 0;
    } while(id2 != id);

    throw NoParamToThisNameException(name);
}


LstParameters& LstParameters::operator=(LstParameters otherLst)
{
    this->clear();
    this->reserve(otherLst.sizeMax);

    std::vector<std::string> names = otherLst.getNameOfAllParameters();

    for (size_t i = 0; i < names.size(); i++)
    {
        this->insert(otherLst[names[i].c_str()]);
    }

    return *this;
}

size_t LstParameters::size() const
{
    return this->s;
}

bool LstParameters::empty() const
{
    return this->s == 0;
}

std::vector<std::string> LstParameters::getNameOfAllParameters() const
{
    std::vector<std::string> names;

    for (size_t i = 0; i < this->parameters.size(); i++)
    {
        if (this->parameters[i].getShortName() != NAME_PARAM_NULL)
        {
            names.push_back(this->parameters[i].getShortName());
        }
    }

    return names;
}

void LstParameters::reserve(size_t _s)
{
    size_t newSize = _s * SUB_LEVEL;

    if (this->sizeMax > _s)
        this->resize(_s);
    else
    {
        this->parameters.reserve(newSize);

        for (size_t i = this->sizeMax * SUB_LEVEL; i < newSize; i++)
        {
            this->parameters.push_back(Parameter());
        }

        this->sizeMax = _s;
    }
}

void LstParameters::resize(size_t _s)
{
    this->sizeMax = _s;

    std::vector<Parameter> newVector;
    newVector.reserve(_s * SUB_LEVEL);


    for (size_t i = 0; i < _s * SUB_LEVEL; i++)
    {
        newVector.push_back(Parameter());
    }

    for (size_t i = 0; i < this->parameters.size(); i++)
    {
        if (this->parameters[i].getShortName() != NAME_PARAM_NULL)
        {
            size_t id = this->hachageFct(this->parameters[i].getShortName());

            size_t id2 = id;
            do
            {
                if (newVector[id2].getShortName() == NAME_PARAM_NULL)
                {
                    newVector[id2] = this->parameters[i];
                    break;
                }
                id2++;
                if (id2 >= newVector.size())
                    id2 = 0;
            } while(id2 != id);
        }
    }

    this->parameters = newVector;
}

inline size_t LstParameters::hachageFct(std::string name) const
{
    return (std::accumulate(name.begin(), name.end(), 0) % this->sizeMax)*SUB_LEVEL;
}

LstParameters::iterator LstParameters::iterator::operator++()
{
    do
    {
        std::vector<Parameter>::const_iterator::operator++();
        this->id += 1;
    }   while(  this->id != int(this->sizeListe) &&
            ((std::vector<Parameter>::const_iterator)*this)->getShortName() == NAME_PARAM_NULL);
    
    if(this->id >= int(this->sizeListe))
        this->id = -1;

    return iterator(*this, this->sizeListe, this->id);
}

LstParameters::iterator LstParameters::iterator::operator++(int)
{
    do
    {
        std::vector<Parameter>::const_iterator::operator++();
        this->id += 1;
    }   while(  this->id != int(this->sizeListe) &&
            ((std::vector<Parameter>::const_iterator)*this)->getShortName() == NAME_PARAM_NULL);
    
    if(this->id >= int(this->sizeListe))
        this->id = -1;
    
    return iterator(*this, this->sizeListe, this->id);
}

bool LstParameters::iterator::operator!=(const iterator ir)
{
    /*
    std::vector<Parameter>::const_iterator l = *this;
    std::vector<Parameter>::const_iterator r = ir;
    */
    return this->id != ir.id;
}

LstParameters::iterator::iterator(std::vector<Parameter>::const_iterator it, size_t _sizeListe, int _id) : 
    std::vector<Parameter>::const_iterator(it), sizeListe(_sizeListe), id(_id)
{ 
    if(id >= int(sizeListe))
        id = -1;
}