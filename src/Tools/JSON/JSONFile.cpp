#include "Tools/JSON/JSONFile.h"

#include <fstream>
#include <vector>
#include <math.h>

#include <iostream>

using namespace Alfodr::JSON;

void readCharNoEspace(std::ifstream& file, char c)
{
    std::string reading = "";
    
    char cReading;
    while (file.get(cReading))
    {
        if(' ' == cReading || '\n' == cReading || '\t' == cReading )
            continue;
        else if(cReading == c)
            return;
        
        throw ERRORReadJSONFileException();
    }

}

std::string readUntilChar(std::ifstream& file, char c)
{
    std::string reading = "";
    bool passed = false;

    char cReading;
    while (file.get(cReading))
    {
        if(cReading == '\\')
            passed = true;
        else if(cReading == c && passed == false)
            return reading;
        else
            passed = false;
        reading.push_back(cReading);
    }

    throw ERRORReadJSONFileException();
}

double readNumber(std::ifstream& file, char cReading)
{
    bool negatif = false;
    if(cReading == '-')
    {
        negatif = true;
        file.get(cReading);
    }

    double value = 0;
    size_t virgule = 0, number;
    do
    {
        if(' ' == cReading || '\n' == cReading || '\t' == cReading )
            continue;
        switch (cReading)
        {
            case '}':
                file.unget();
            case ',':
                return negatif ? -value : value;
            case '0':
                number = 0;
                break;
            case '1':
                number = 1;
                break;
            case '2':
                number = 2;
                break;
            case '3':
                number = 3;
                break;
            case '4':
                number = 4;
                break;
            case '5':
                number = 5;
                break;
            case '6':
                number = 6;
                break;
            case '7':
                number = 7;
                break;
            case '8':
                number = 8;
                break;
            case '9':
                number = 9;
                break;
            case '.':
                if(virgule != 0)
                    throw ERRORReadJSONFileException();
                virgule = 1;
                break;
            default:
                throw ERRORReadJSONFileException();
        }
        if(virgule == 0)
        {
            value*=10;
            value+=number;
        }
        else
        {
            if(virgule > 1)
            {
                double n = pow(double(10), virgule - 1);
                value += double(number)/n;
            }
            virgule++;
        }
    }
    while (file.get(cReading));

    throw ERRORReadJSONFileException();
}

Objet readObjet(std::ifstream& file);

Value readValue(std::ifstream& file)
{
    char cReading;
    while (file.get(cReading))
    {
        if (' ' == cReading || '\n' == cReading || '\t' == cReading)
            continue;
        break;
    }
    

    Value value = Value();
    switch (cReading)
    {
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            value.setValue(readNumber(file, cReading));
            break;
        case '"':
            value.setValue(readUntilChar(file, '"').c_str());
            value.setValue(true);
            break;
        case '{':
            value.setValue(readObjet(file));
            break;
        case '[':
            value.asTable();
            while(true)
            {
                value.append(readValue(file));


                while (file.get(cReading))
                {
                    if (' ' == cReading || '\n' == cReading || '\t' == cReading)
                        continue;
                    break;
                }

                if (',' == cReading)
                    continue;
                else if (']' == cReading)
                    break;
            }


            break;
        case 't':
        case 'T':
            file.get(cReading); if (cReading != 'R' && cReading != 'r') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'U' && cReading != 'u') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'E' && cReading != 'e') throw ERRORReadJSONFileException();
            value.setValue(true);
            break;
        case 'f':
        case 'F':
            file.get(cReading); if (cReading != 'A' && cReading != 'a') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'L' && cReading != 'l') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'S' && cReading != 's') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'E' && cReading != 'e') throw ERRORReadJSONFileException();
            value.setValue(false);
            break;
        case 'n':
        case 'N':
            file.get(cReading); if (cReading != 'U' && cReading != 'u') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'L' && cReading != 'l') throw ERRORReadJSONFileException();
            file.get(cReading); if (cReading != 'L' && cReading != 'l') throw ERRORReadJSONFileException();
            break;
        default:
            throw ERRORReadJSONFileException();
    }

    return value;
}

Objet readObjet(std::ifstream& file)
{
    char cReading;
    Objet obj = NewObjet();

    while (file.get(cReading))
    {
        // Read nom pair
        if(' ' == cReading || '\n' == cReading || '\t' == cReading || ',' == cReading )
            continue;
        else if(cReading == '}' )
            return obj;
        else if('"' == cReading || '\'' == cReading)
        {
            std::string namePair = readUntilChar(file, cReading);
            readCharNoEspace(file, ':');

            
            obj->insertPair(Pair(namePair.c_str(), readValue(file)));
        }
        else
            break;
    }

    throw ERRORReadJSONFileException();

}

Objet Alfodr::JSON::openJSONFile(const char * path) 
{
    std::ifstream file = std::ifstream(path);
    std::vector<Objet> objets;

    readCharNoEspace(file, '{');

    char c = '{';
    Objet root =  readObjet(file);

    file.close();
    return root;
}

void writePair(std::ofstream& file, Pair pair, std::string tab);


void writeObjet(std::ofstream& file, Objet objet, std::string tab)
{
    file << "{\n";

    std::vector<std::shared_ptr<Pair>> pairs = objet->getPairs();

    std::string newtab = tab + "\t";

    for(size_t i = 0; i < pairs.size(); i++)
    {
        file << newtab;
        writePair(file, *(pairs[i].get()), newtab);

        if(i != pairs.size()-1)
            file << ",";
        file << "\n";
    }

    file << tab;
    file << "}";
}

void writeValue(std::ofstream& file, Value value, std::string tab)
{
    switch (value.getType())
    {
    case TYPE_VALUE::VALUE_NULL:
        file << "null";
        break;
    case TYPE_VALUE::VALUE_NUMBER_I:
        file << value.asInt();
        break;
    case TYPE_VALUE::VALUE_NUMBER_D:
        file << value.asDouble();
        break;
    case TYPE_VALUE::VALUE_BOOL:
        if (value.asBool())
            file << "true";
        else
            file << "false";
        break;
    case TYPE_VALUE::VALUE_STRING:
        file << '"' << value.asString() << '"';
        break;
    case TYPE_VALUE::VALUE_OBJET:
        writeObjet(file, value.asObjet(), tab);
        break;
    case TYPE_VALUE::VALUE_TABLE:
        std::vector<Value> values = value.asTable();
        std::string newtab = tab + "\t";
        file << "[\n";
        for (size_t i = 0; i < values.size(); i++)
        {
            file << newtab;
            writeValue(file, values, newtab);
            if (i < values.size() - 1)
                file << ",\n";
        }
        file << tab << "]\n";

        break;
    }
}

void writePair(std::ofstream& file, Pair pair, std::string tab)
{
    file << '"' << pair.getKey() << "\": ";
    writeValue(file, pair, tab);
}

void Alfodr::JSON::writeJSONFile(const char * path, Objet objet) 
{
    std::ofstream file = std::ofstream(path);



    writeObjet(file, objet, "");

    file.close();
}