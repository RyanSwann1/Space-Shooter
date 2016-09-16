#include "GUI.h"

GUI::GUI()
{
}

GUI::~GUI()
{
	purgeEntries();
}

bool GUI::hasEntry(const std::string & name)
{
	return false;
}

void GUI::updateEntry(const std::string & name, const std::string& text)
{
	for (auto iter = m_entries.begin(); iter != m_entries.end(); iter++)
	{
		if (iter->first == name)
		{
			iter->second->m_text.setString(text); 
			return;
		}
	}
}

void GUI::updateEntry(const std::string& name, GUIEntry* entry)
{
	for (auto iter = m_entries.begin(); iter != m_entries.end(); iter++)
	{
		if (iter->first == name)
		{
			iter->second = entry;
		}
	}
}

void GUI::draw(sf::RenderWindow & window)
{
	auto entriesCopy = m_entries;

	for (auto iter = entriesCopy.begin(); iter != entriesCopy.end(); iter++)
	{
		window.draw(iter->second->m_text);
	}
}

void GUI::purgeEntries()
{
	for (auto &i : m_entries)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_entries.clear();
}
