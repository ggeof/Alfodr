#include "SoftwareManager/User/User.h"
#include <cstdarg>
#include <cstring>

Alfodr::SoftwareManager::_User::_User() :
	Logs((std::string(FOLDER_USER_APPLICATIONS)+"/logs").c_str()), Setup((std::string(FOLDER_USER_APPLICATIONS) + "/config.json").c_str()),
	levelUser(OPERATOR)
{
	passwords.insert(std::pair<LevelUser, char*>(UT, ""));
	passwords.insert(std::pair<LevelUser, char*>(OPERATOR, ""));
	passwords.insert(std::pair<LevelUser, char*>(ADMINISTRATOR, ""));
	passwords.insert(std::pair<LevelUser, char*>(DEVELOPPER, ""));
	passwords.insert(std::pair<LevelUser, char*>(GOD,""));
}

Alfodr::SoftwareManager::_User::~_User()
{
	passwords.clear();
}

bool Alfodr::SoftwareManager::_User::loging(LevelUser user, char* password)
{
	if (strcmp("", passwords.at(user)) == 0)
		throw PasswordOfUserNotDefined(user);

	if (strcmp(password, passwords.at(user)) == 0)
	{
		this->levelUser = user;
		return true;
	}

	return false;
}

void Alfodr::SoftwareManager::_User::writeLog(const char* msg)
{
	bool writeConsole = this->levelUser >= LevelUser::DEVELOPPER || this->levelUser == LevelUser::UT;
	if (msg[0] == '*')
	{
		writeConsole = true;
		msg = std::string(msg).substr(1).c_str();
	}
	if (writeConsole)
		std::cout << msg << std::endl;

	Logs::writeLog(msg);
}

void Alfodr::SoftwareManager::_User::operator<<(const char* msg)
{
	this->writeLog(msg);
}

void Alfodr::SoftwareManager::_User::setPassword(size_t nbPasswordSet, ...)
{
	va_list list;
	va_start(list, nbPasswordSet);

	for (size_t i = 0; i < nbPasswordSet; i++)
	{
		LevelUser level = LevelUser(va_arg(list, int));
		this->passwords[level] = va_arg(list, char*);
	}

	va_end(list);
}
