#include "Tools/CSV/FileCSV.h"
#include <algorithm>
#include <string>
#include <sstream>

using namespace Alfodr::CSV;

FileCSV::FileCSV(std::string nameFile, std::string textHeader) :
    Table(0, textHeader)
{
    std::string ext = ".csv";
    // On vérifie si l'extension est mise sinon on la met
    if(0 != nameFile.compare(nameFile.length()-ext.length(), ext.length(), ext))
        nameFile += ext;

    file = std::ofstream(nameFile);
    assert(file.is_open());
}


FileCSV::~FileCSV() 
{
    file.close();
}

void FileCSV::writeInFile(bool writeHeaders) 
{
    if(writeHeaders)
        this->writeHeader();

    if(this->columns.size() == 0)
        return;

    size_t nbElement = this->columns[0].getNbElement();

    for(size_t i=0; i < nbElement; i++)
    {
        this->file<<"\n";
        for(size_t j=0; j < this->columns.size(); j++)
        {
            this->file<<this->columns[j].getElement(i)<<";";
        }
    }
}

void FileCSV::writeInFile(std::string text) 
{
    this->file<<text;
}

void FileCSV::writeHeader() 
{
    if(this->headerWritten == -1)
    {
        if(this->getTitle() != "")
            this->file<<this->getTitle() + "\n";

        this->headerWritten = 0;
    }


    for(size_t i = this->headerWritten; i < this->columns.size(); i++)
        this->file<<this->columns[i].getTitle()+";";

}

Table FileCSV::fromFileCSV(std::string path, bool titleColumn, char separator) 
{
    std::ifstream file(path);

    if(!file.is_open())
        throw "Could not open file "+path;

    Table table(0, path);

    std::string line, col;
    std::vector<std::string> lstLine;

    if(!std::getline(file, line))
        return table;

    if(titleColumn)
    {
        std::stringstream values(line);

        while(std::getline(values, col, separator)){
            while(true)
            {
                try
                {
                    table.addColumn(col);
                    break;
                }
                catch(const std::string& e)
                {
                    col = "_"+col;
                }
            }
        }
    }
    else
    {
        std::stringstream values(line);

        while(std::getline(values, col, separator)){
            table.addColumn("");
            lstLine.push_back(col);
        }
        table.addLine(lstLine);
        lstLine.clear();
    }


    while(std::getline(file, line))
    {
        std::stringstream values(line);

        while(std::getline(values, col, separator)){
            lstLine.push_back(col);
        }
        table.addLine(lstLine);
        lstLine.clear();
    }

    return table;
}