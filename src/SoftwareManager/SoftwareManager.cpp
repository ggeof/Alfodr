#include "SoftwareManager/User/User.h"
#include <experimental/filesystem>


void Alfodr::SoftwareManager::initSoftwareAlfodr(const char* softwareName)
{
	SOFTWARE_NAME = softwareName;


	std::string littleName = std::string(softwareName);
	std::transform(littleName.begin(), littleName.end(), littleName.begin(),
			[](unsigned char c) { return std::tolower(c); } // correct
	);

	FOLDER_RESSOURCE_APPLICATIONS = ("opt/" + littleName + "/").c_str();
	if(!std::experimental::filesystem::exists(FOLDER_RESSOURCE_APPLICATIONS))
		FOLDER_RESSOURCE_APPLICATIONS ="./";

#ifdef LINUX
	std::string home = std::string(getenv("HOME"));
	FOLDER_USER_APPLICATIONS = (home + "/." + littleName).c_str();
	system(("mkdir -p -m 776 " + std::string(FOLDER_USER_APPLICATIONS)).c_str());
#endif // LINUX

	//auto user = User::value();
}