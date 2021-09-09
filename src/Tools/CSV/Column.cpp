#include "Tools/CSV/Column.h"

using namespace Alfodr::CSV;

Column::Column(std::string _header) : title(_header)
{
    elems.reserve(1);
}

void Column::addElement(std::string elem) 
{
    this->elems.push_back(elem);
}


void Column::cleanColumn() 
{
    this->elems.clear();
}



std::string Column::getTitle() const
{
	return this->title;
}
