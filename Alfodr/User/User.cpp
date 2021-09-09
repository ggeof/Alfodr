#include "User.h"

User::User(TypeUser userBase, std::string _fileConfig)
    : Logs(userBase == TypeUser::UT), Config(_fileConfig), typeUser(userBase)
{
    if(!this->isLoaded())
        *this << "ERROR : Loading file config : " + _fileConfig;
}

User::~User() 
{
    
}

bool User::changeUser(std::string password) 
{
    if(password == "333333")
    {
        this->typeUser = Developer;
        return true;
    }
    else if(password == "111111")
    {
        this->typeUser = Administrator;
        return true;
    }
    else if(password == "000000")
    {
        this->typeUser = Operator;
        return true;
    }

    this->typeUser = Operator;
    return false;
}

void User::ecrireLog(std::string text) 
{
    if(text.at(0) == '*' || this->typeUser==TypeUser::UT)
        std::cerr << text << std::endl;
    else
    {
        if(this->typeUser>=TypeUser::Developer)
            std::cerr << text << std::endl;
        Logs::ecrireLog(text);
    }
}