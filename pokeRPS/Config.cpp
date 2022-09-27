#include "Config.h"

Config::Config()
{
	if (std::filesystem::exists("./settings.config"))
		this->deserialize();
	else
	{
		this->volume = this->defaultVolume;
		this->scrollSpeed = this->defaultScrollSpeed;
		this->bgColor = this->defaultBgColor;
	}
}

Config::~Config()
{
	this->serialize();
}

void Config::serialize()
{
	std::ofstream ofstream("./settings.config", std::ios::out | std::ios::binary);

	ofstream.write((char*)this + (sizeof(*this) / 2), sizeof(*this) / 2);

	ofstream.close();
}

void Config::deserialize()
{
	std::ifstream ifstream("./settings.config", std::ios::in | std::ios::binary);

	Config* deserializedByteStream = (Config*)malloc(sizeof(*this) / 2);
	ifstream.read((char*)deserializedByteStream, sizeof(*this) / 2);

	if (!deserializedByteStream)
	{
		this->volume = this->defaultVolume;
		this->scrollSpeed = this->defaultScrollSpeed;
		this->bgColor = this->defaultBgColor;
		return;
	}

	this->volume = deserializedByteStream->defaultVolume;
	this->scrollSpeed = deserializedByteStream->defaultScrollSpeed;
	this->bgColor = deserializedByteStream->defaultBgColor;

	ifstream.close();
}

void Config::reset()
{
	std::filesystem::remove("./settings.config");

	this->volume = this->defaultVolume;
	this->scrollSpeed = this->defaultScrollSpeed;
	this->bgColor = this->defaultBgColor;
}
	 
void Config::setAll(unsigned volume, float scrollSpeed, glm::vec3 bgColor)
{
	this->volume = volume;
	this->scrollSpeed = scrollSpeed;
	this->bgColor = bgColor;
}
