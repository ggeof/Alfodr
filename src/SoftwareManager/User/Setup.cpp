#include "SoftwareManager/User/Setup.h"

#include <experimental/filesystem>
#include <cstring>

using namespace Alfodr;

Alfodr::SoftwareManager::Setup::Setup(const char* _fileConfig, const char* _fileDefault) :
	fileConfig(_fileConfig), fileConfigDefault(_fileDefault)
{
	if (!std::experimental::filesystem::exists(this->fileConfigDefault))
		fileConfigDefault = "";

	if (std::experimental::filesystem::exists(this->fileConfig))
		this->root = JSON::openJSONFile(this->fileConfig);
	else if(strcmp(fileConfigDefault, "") != 0)
		this->root = JSON::openJSONFile(this->fileConfigDefault);
	else
		this->root = JSON::NewObjet();

}

Alfodr::SoftwareManager::Setup::~Setup()
{

}


JSON::Objet Alfodr::SoftwareManager::Setup::getCollectionParameters(const char* nameCollection)
{
	std::vector<std::shared_ptr<JSON::Pair>> pairs = this->root->getPairs();

	while (pairs.size() > 0)
	{
		auto p = pairs.front();
		pairs.erase(pairs.begin());

		if (strcmp(nameCollection, p->getKey()) == 0)
		{
			JSON::Objet o = (*p.get());
			p->setValue(o);
			return o;
		}
		else if (p->getType() == JSON::TYPE_PAIR::PAIR_OBJET)
		{
			auto prs = p->asObjet()->getPairs();
			pairs.insert(prs.begin(), prs.end(), prs.begin());
		}
	}

	JSON::Objet objet = JSON::NewObjet();
	this->root->getPair(nameCollection)->setValue(objet);
	return objet;
}

std::shared_ptr<JSON::Pair> Alfodr::SoftwareManager::Setup::getParameters(const char* nameParamters)
{
	std::vector<std::shared_ptr<JSON::Pair>> pairs = this->root->getPairs();

	while (pairs.size() > 0)
	{
		auto p = pairs.front();
		pairs.erase(pairs.begin());

		if (strcmp(nameParamters, p->getKey()) == 0)
		{
			pairs.clear();
			return p;
		}
		else if (p->getType() == JSON::TYPE_PAIR::PAIR_OBJET)
		{
			auto prs = p->asObjet()->getPairs();
			pairs.insert(prs.begin(), prs.end(), prs.begin());
		}
	}
	
	return this->root->getPair(nameParamters);
}

void Alfodr::SoftwareManager::Setup::save()
{
	JSON::writeJSONFile(this->fileConfig, this->root);
}

void Alfodr::SoftwareManager::Setup::reloadDefault()
{
	if (strcmp(fileConfigDefault, "") != 0)
		this->root = JSON::openJSONFile(this->fileConfigDefault);
}

void Alfodr::SoftwareManager::Setup::setConfigurationInDefault()
{
	if (strcmp(fileConfigDefault, "") != 0)
		JSON::writeJSONFile(this->fileConfigDefault, this->root);
}
