#include "Config.h"

Config::Config(std::string _fileConfig) 
{
    
	nameDirectory = std::string(getenv("HOME"))+"/Caliper/";
    
    std::ifstream fileConfigR(_fileConfig); 
    if(!fileConfigR.is_open())
    {
        // Si ça a échoué on retente avec le fichier de base
        fileConfigR.open("/opt/caliper/ressources/Config/Configuration_Bases.json");   
    }
    
    if(fileConfigR.is_open())
    {
        Json::Reader fJsonR;
        loaded = fJsonR.parse(fileConfigR, root);
    }
    fileConfigR.close();

    if(_fileConfig == "/opt/caliper/ressources/Config/Configuration_Bases.json")
         _fileConfig = nameDirectory+"/Config.json"; // On évite de réécrire dessu

    // On vérifie qu'on pourra ouvrir le fichier par la suite
    std::ofstream fileConfigW(_fileConfig, std::ios::app);   

    if(!fileConfigW.is_open())
        throw std::string("ERROR Open File Config !");
    
    fileConfig = _fileConfig;
}

Config::~Config() 
{

}

Json::Value Config::loadParameters(std::string typeParameters) 
{
    try
    {;
        return this->root
            .get(typeParameters, Json::Value());
    }
    catch(const Json::LogicError& e)
    {
        return Json::Value();
    }
    
}

void Config::saveParameters(std::string typeParameters, Json::Value & values) 
{
    try
    {
        std::ofstream fileConfigW(this->fileConfig);  
        root[typeParameters] = values; 

        // Ecriture
        Json::StreamWriterBuilder builder;
        fileConfigW << Json::writeString(builder, root);
        fileConfigW.close();
    }
    catch(const Json::LogicError& e)
    {

    }
}

bool Config::isLoaded() 
{
    return this->loaded;
}

std::string Config::getNameDirectory()
{
    return this->nameDirectory; 
}
