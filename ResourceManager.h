#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Utilities.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

template <class T>
class ResourceManager
{
public:
	ResourceManager() {}
	virtual ~ResourceManager() {}

	T* getResource(const std::string& id)
	{
		auto res = find(id);
		return (res ? res->first : nullptr);
	}

	bool requireResource(const std::string& id)
	{
		auto res = find(id);
		if (res)
		{
			res->second++;
			return true;
			
		}
		T* resource = loadFromFilePath(id);
		if (resource)
		{
			m_resources.emplace(id, std::make_pair(resource, 1));
			return true;
		}
		return false;
	}

	void unloadResource(const std::string& id)
	{
		auto res = find(id);
		if (res)
		{
			if (res->second) {
				res->second--;
			}
			else
			{
				destroyResource(id);
			}
		}
	}


protected:
	std::unordered_map<std::string, std::string> m_filePath; //name of file, file path
	virtual T* loadFromFilePath(const std::string& id) = 0;
	virtual void loadInResources(const std::string& fileName) = 0;

	void registerFilePath(const std::string& fileName, const std::string& filePath)
	{
		if (m_filePath.find(fileName) == m_filePath.cend())
		{
			m_filePath.emplace(fileName, filePath);
		}
		
	}

	void purgeResources()
	{
		for (auto &i : m_resources)
		{
			delete i.second.first;
		}

		m_resources.clear();
	}

private:
	std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources; //Name of resource, resource and how many times resource is in use
	
	std::pair<T*, unsigned int>* find(const std::string& id)
	{
		auto iter = m_resources.find(id);
		return (iter != m_resources.end() ? &iter->second : nullptr);	
	}

	void destroyResource(const std::string& id)
	{
		auto iter = m_resources.find(id);
		if (iter != m_resources.cend())
		{
			delete iter->second.first;
		}
	}
};
#endif // !RESOURCE_MANAGER_H
