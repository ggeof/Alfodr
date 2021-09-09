#include "User/User.h"

User user;




#ifdef DEBUG
std::cout << "### MODE DEBUG ###" << std::endl;
std::cout << "Opencv version : " << CV_VERSION << std::endl;
//imshow("Test", cv::Mat(10,10, uchar(0)));
#endif

#ifdef CUDA
cv::cuda::getCudaEnabledDeviceCount();
cv::cuda::setDevice(0);
#endif // CUDA

// On charge gtk
XInitThreads();
gtk_init(&argc, &argv);


// Si on est pas placé dans le bon dossier on s'y place
if (!experimental::filesystem::exists("./ressources"))
chdir("/opt/caliper/");


std::string home = std::string(getenv("HOME"));


void Alfodr::SoftwareManager::initSoftwareAlfodr(const char* softwareName)
{
	SOFTWARE_MANAGER = softwareName;


	std::string littleName = std::string(softwareName);
	std::transform(littleName.begin(), littleName.end(), littleName.begin(),
			[](unsigned char c) { return std::tolower(c); } // correct
		);

#ifdef LINUX
	std::string home = std::string(getenv("HOME"));
	FOLDER_USER_APPLICATIONS = (home + "/." + littleName).c_str();
	system(("mkdir -p -m 776 " + std::string(FOLDER_USER_APPLICATIONS)).c_str());
#endif // LINUX

	user = User::value();
}