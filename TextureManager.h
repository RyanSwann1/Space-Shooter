#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "ResourceManager.h"
#include "Utilities.h"
#include <SFML\Graphics.hpp>
#include <iostream>
class TextureManager :
	public ResourceManager<sf::Texture>
{
public:
	TextureManager(const std::string& fileName)
	{
		loadInResources(fileName);
	}

	~TextureManager() 
	{
		purgeResources();
	}

	sf::Texture* loadFromFilePath(const std::string& id) override
	{
		//Search through existing file paths for each texture
		auto iter = m_filePath.find(id);
		if (iter != m_filePath.cend())
		{
			sf::Texture* texture = new sf::Texture;
			if (!texture->loadFromFile(iter->second)) 
			{
				delete texture;
				texture = nullptr;
				return nullptr;
			}
			return texture;
		}		
		return nullptr;
	}

private:
	void loadInResources(const std::string& fileName) override
	{
		std::ifstream file;
		file.open(Utilities::getResourcesLocation() + fileName);
		if (!file.is_open())
		{
			std::cerr << "Unable to open file: " << fileName << "\n";
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
#endif // !TEXTURE_MANAGER_H

