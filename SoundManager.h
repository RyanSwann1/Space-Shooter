#pragma once
#include "ResourceManager.h"
#include <SFML\Audio.hpp>
class SoundManager
	: public ResourceManager<sf::SoundBuffer>
{
public:
	SoundManager(const std::string& file)
	{
		loadInResources(file);
	}

	~SoundManager()
	{
		purgeResources();
	}

	sf::SoundBuffer* loadFromFilePath(const std::string& id) override
	{
		auto iter = m_filePath.find(id);
		if (iter != m_filePath.cend())
		{
			sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;
			if (!soundBuffer->loadFromFile(iter->second))
			{
				delete soundBuffer;
				soundBuffer = nullptr;
				return nullptr;
			}
			return soundBuffer;
		}
		return nullptr;
	}

private:
	void loadInResources(const std::string& fileName)
	{
		std::ifstream file;
		file.open(Utilities::getResourcesLocation() + fileName);
		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << fileName << "n";
		}
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == '/') {
				continue;
			}
			std::stringstream keyStream(line);
			std::string name;
			std::string location;
			keyStream >> name >> location;
			registerFilePath(name, location);
			std::cout << name << location << "\n";
		}
		file.close();
	}
};