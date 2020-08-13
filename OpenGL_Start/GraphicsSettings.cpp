#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings() {
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();

}

GraphicsSettings::~GraphicsSettings()
{
}

void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path.c_str());

	if (ofs.is_open()) {
		ofs << title;
		ofs << this->resolution.width << " " << resolution.height;
		ofs << this->fullscreen;
		ofs << this->frameRateLimit;
		ofs << this->verticalSync;
		ofs << this->contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path.c_str());

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> this->resolution.width >> resolution.height;
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit;
		ifs >> this->verticalSync;
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();
}