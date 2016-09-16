#pragma once

#include "ResourceManager.h"
#include "Utilities.h"
#include <SFML\Graphics\Font.hpp>

class FontManager :
	public ResourceManager<sf::Font>
{
public:
	FontManager(const std::string& fileName)
	{
		loadInResources(fileName);
	}

	~FontManager()
	{
		purgeResources();
	}
	
private:
	sf::Font* loadFromFilePath(const std::string& id) override
	{
		sf::Font* font = new sf::Font;
		auto iter = m_filePath.find(id);
		if (iter != m_filePath.cend())
		{
			if (!font->loadFromFile(Utilities::getResourcesLocation() + iter->second))
			{
				delete font;
				font = nullptr;
				return nullptr;
			}
			return font;
		}
		return nullptr;
	}

	void loadInResources(const std::string& fileName) override
	{
		std::ifstream file;
		file.open(Utilities::getResourcesLocation() + fileName);
		if (!file.is_open())
		{
			std::cerr << "Couldn't open file: " << fileName << "\n";
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
		}
		file.close();
	}
};