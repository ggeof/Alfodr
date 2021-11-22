#include "SoftwareManager/ArgumentReader.h"
#include "SoftwareManager/SoftwareManager.h"
#include <iostream>
#include <cstring>


using namespace Alfodr::SoftwareManager;

ArgumentReader::ArgumentReader() 
{
    this->arguments.push_back(Argument{
        "help",
        "h",
        "Show this text",
        nullptr,
        true
    });
}

ArgumentReader::~ArgumentReader() 
{
    this->arguments.clear();
}

void ArgumentReader::addArgument(Argument arg) 
{ 
    this->arguments.push_back(arg);
}

void ArgumentReader::addArgument(std::vector<Argument> args) 
{
    
    this->arguments.insert(args.begin(), args.end(), args.begin());
}

std::vector<Argument> ArgumentReader::readArgument(int argc, char * arg[]) 
{
    std::vector<Argument> args;
    
    try
    {
    
        for (size_t i = 1; i < argc; i++)
        {
            size_t a;
            for (a = 0; a < this->arguments.size(); a++)
            {
                if(strcmp(arg[i], ("--"+std::string(this->arguments[a].name)).c_str()) == 0 || (
                    strcmp(this->arguments[a].shortName,"") != 0 && strcmp(arg[i], ("-"+std::string(this->arguments[a].shortName)).c_str()) == 0) )
                {
                    if(this->arguments[a].noValue)
                    {
                        this->arguments[a].value = "";
                    }
                    else
                    {
                        a++;
                        if(a == this->arguments.size())
                            throw MissingValueForArgument(arg[i]);

                        this->arguments[a].value = arg[i];
                    }
                    args.push_back(this->arguments[a]);
                    break;
                }
            }
            if(a == this->arguments.size())
                throw ArgumentNotRecognized(arg[i]);
        }
    }
    catch(const ArgumentNotRecognized& e)
    {
        std::cout << e.what() << std::endl;
        this->showHelper();
        throw e;
    }
    catch(const MissingValueForArgument& e)
    {
        std::cout << e.what() << std::endl;
        this->showHelper();
        throw e;
    }
    

    return args;
}

void ArgumentReader::showHelper() const
{
    if(SOFTWARE_NAME != nullptr)
        std::cout << SOFTWARE_NAME << " helper" << std::endl;
    for (size_t i =  0; i < this->arguments.size(); i++)
    {
        std::cout << "--" << this->arguments[i].name;
        if(strcmp(this->arguments[i].shortName,"") != 0)
            std::cout << ", " << "-" << this->arguments[i].shortName<< ", ";
        if(strcmp(this->arguments[i].helper,"") != 0)
            {
            std::cout << " :" << std::endl;
            std::cout << "\t" << this->arguments[i].helper;

        }
        std::cout << std::endl;
    }   
}