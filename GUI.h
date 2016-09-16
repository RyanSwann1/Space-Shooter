#pragma once

#include "GUIEntry.h"
#include <vector>
#include <vector>
class GUI
{
public:
	GUI();
	~GUI();

	void addEntry(const std::string& name, GUIEntry* entry) { m_entries.emplace_back(std::make_pair(name, entry)); }
	bool hasEntry(const std::string& name);
	void removeEntry(const std::string& name) {}

	void updateEntry(const std::string& name, const std::string& text); //Update entry text
	void updateEntry(const std::string& name, GUIEntry* entry); //Update entry
	
	void draw(sf::RenderWindow& window);

	void purgeEntries();

private:
	std::vector<std::pair<std::string, GUIEntry*>> m_entries;

};

