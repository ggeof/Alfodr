#include "Tools/CSV/Table.h"

#include <cstdarg>

using namespace Alfodr::CSV;

Table::Table(int nbColumns, std::string _title) :
    title(_title)
{    
    this->columns.reserve(nbColumns);
}

Table::~Table() 
{
    this->removeAllColums();
}

void Table::addColumn(std::string title) 
{
    if(title != "")
        for(size_t i = 0; i < this->columns.size(); i++)
            if((std::string) this->columns[i] == title)
                throw "Column \"" + title + "\" already exists !";

    this->columns.push_back(Column(title));

    Column cAdd = this->columns[this->columns.size()-1];

    for(size_t i = 0; i < this->columns[0].elems.size(); i++)
        cAdd.addElement("");
}

void Table::cleanAllColums() 
{
    for(size_t i = 0; i < this->columns.size(); i++)
        this->columns[i].cleanColumn();
}

void Table::removeAllColums() 
{
    this->cleanAllColums();
    this->columns.clear();
}

void Table::addLine(std::vector<std::string> line) 
{
    size_t i;
    for(i = 0; i < line.size() && i < this->columns.size(); i++)
    {
        this->columns[i].addElement(line[i]);
    }
    for(i = line.size(); i < this->columns.size(); i++)
    {
        this->columns[i].addElement("");
    }

}

void Table::addLine(int nbArgs, ...) 
{
    va_list args;
    va_start(args, nbArgs);

    if(nbArgs < 0 ||(size_t) nbArgs > this->columns.size())
        nbArgs = this->columns.size();

    size_t i;
    for(i = 0; i <(size_t) nbArgs; i++)
    {
        std::string arg = va_arg(args, char*);
        this->columns[i].addElement(arg);
    }
    for(i = i; i < this->columns.size(); i++)
    {
        this->columns[i].addElement("--");
    }

    va_end(args); 
}

size_t Table::getNbLine() const
{
    if(this->columns.size() == 0)
        return 0;
    return this->columns[0].getNbElement();
}

size_t Table::getNbColumn() const
{
    return this->columns.size();
}

std::string Table::getTitle() const
{
	return this->title;
}

Column Table::getColumn(std::string title) const
{
    for(size_t i = 0; i < this->columns.size(); i++)
        if((std::string) this->columns[i] == title)
            return this->columns[i];

    throw "No column with the title \"" + title + "\" exists !";
}

std::vector<std::string> Table::getLine(size_t nbLine) const
{
    std::vector<std::string> line;

    if(this->columns.size() == 0 || this->columns[0].elems.size() < nbLine)
        return line;

    for(size_t i = 0; i < this->columns.size(); i++)
        line.push_back(this->columns[i].elems[nbLine]);

    return line;
}
