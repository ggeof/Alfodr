#include "Tools/JSON/JSONFile.h"

#include <fstream>
#include <vector>
#include <math.h>

using namespace Alfodr::JSON;

void readCharNoEspace(std::ifstream& file, char c)
{
    std::string reading = "";

    char cReading;
    while (file.get(cReading))
    {
        if(' ' == cReading || '\n' == cReading || '\t' == cReading )
            continue;
        if(cReading == c)
            return;
        throw ERRORReadJSONFileException();
    }

}

std::string readUntilChar(std::ifstream& file, char c)
{
    std::string reading = "";

    char cReading;
    while (file.get(cReading))
    {
        if(cReading == c)
            return reading;
        reading += cReading;
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

Objet readObjet(std::ifstream& file)
{
    Objet obj = NewObjet();

    char cReading;
    while (file.get(cReading))
    {
        if(' ' == cReading || '\n' == cReading || '\t' == cReading )
            continue;
        else if('}' == cReading)
        {
            return obj;
        }
        else if('"' == cReading)
        {
            std::shared_ptr<Alfodr::JSON::Pair> newPair(new Pair(readUntilChar(file, '"').c_str()));
            readCharNoEspace(file, '=');

            while (file.get(cReading))
            {
                if(' ' == cReading || '\n' == cReading || '\t' == cReading )
                    continue;
                break;
            }
            TYPE_PAIR typePair;
            std::shared_ptr<Alfodr::JSON::Pair> pair = nullptr;
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
                    pair->setValue(readNumber(file, cReading));
                    break;
                case '"':
                    pair->setValue(readUntilChar(file, '"').c_str());
                    break;
                case '{':
                    pair->setValue(readObjet(file));
                    break;
                case 't':
                case 'T':
                    file.get(cReading); if(cReading != 'R' && cReading != 'r') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'U' && cReading != 'u') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'E' && cReading != 'e') throw ERRORReadJSONFileException();
                    pair->setValue(true);
                    break;
                case 'f':
                case 'F':
                    file.get(cReading); if(cReading != 'A' && cReading != 'a') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'L' && cReading != 'l') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'S' && cReading != 's') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'E' && cReading != 'e') throw ERRORReadJSONFileException();
                    pair->setValue(false);
                    break;
                case 'n':
                case 'N':
                    file.get(cReading); if(cReading != 'U' && cReading != 'u') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'L' && cReading != 'l') throw ERRORReadJSONFileException();
                    file.get(cReading); if(cReading != 'L' && cReading != 'l') throw ERRORReadJSONFileException();
                    break;
                default:
                    throw ERRORReadJSONFileException();
            }
            readCharNoEspace(file, ',');

            obj->insertPair(pair);
        }
        else
            break;
    }

    throw ERRORReadJSONFileException();

}

Objet openJSONFile(const char * path) 
{
    std::ifstream file = std::ifstream(path);
    std::vector<Objet> objets;

    readCharNoEspace(file, '{');

    Objet root =  readObjet(file);
    file.close();
    return root;
}

void writePair(std::ofstream& file, Pair pair, std::string tab);

void writeObjet(std::ofstream& file, Objet objet, std::string tab)
{
    file << "{\n";

    std::vector<std::shared_ptr<Pair>> pairs = objet->getPairs();

    for(size_t i = 0; i < pairs.size(); i++)
    {
        file << tab;
        writePair(file, *(pairs[i].get()), tab);

        if(i != pairs.size()-1)
            file << ",";
        file << "\n";
    }

    file << "}";
}


void writePair(std::ofstream& file, Pair pair, std::string tab)
{
    file << '"' << pair.getKey() << "\": ";

    switch (pair.getType())
    {
        case TYPE_PAIR::PAIR_NULL :
            file << "null";
            break;
        case TYPE_PAIR::PAIR_NUMBER :
            file << pair.asDouble();
            break;
        case TYPE_PAIR::PAIR_BOOL :
            if(pair.asBool())
                file << "true";
            else
                file << "false";
            break;
        case TYPE_PAIR::PAIR_STRING :
            file << '"' << pair.asString()<< '"' ;
            break;
        case TYPE_PAIR::PAIR_OBJET :
            writeObjet(file, pair.asObjet(), tab + "\t");
            break;
    }
}

void writeJSONFile(const char * path, Objet objet) 
{
    std::ofstream file = std::ofstream(path);



    writeObjet(file, objet, "\t");

    file.close();
}