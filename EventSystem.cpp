#include "EventSystem.h"
#include "SharedContext.h"
#include "StateManager.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>

EventSystem::EventSystem(SharedContext* sharedContext)
	: m_sharedContext(sharedContext), 
	m_hasFocus(true)
{
	loadBindings();
}

EventSystem::~EventSystem()
{

}

void EventSystem::update(sf::Event sfmlEvent)
{
	//sf::Event m_event;
	//Screen is minimized
	if (!m_hasFocus) {
		return;
	}

	//Search through all bindings
	for (auto &bindIter : m_bindings)
	{
		Binding bind = bindIter.second;

		//Search through all events within bindings
		for (auto &eventIter : bind.m_events)
		{
			EventType eventCurrent = (EventType)sfmlEvent.type;
			////Match given event
			switch (eventCurrent)
			{
			case (EventType::KeyPressed) :
			{
				if (eventCurrent == eventIter.first && sfmlEvent.key.code == eventIter.second.m_code)
				{
					activateEvent(bind, m_sharedContext->m_stateManager->getStateCurrent());
				}
				break;
			}
			case (EventType::Closed):
			{
				if (eventCurrent == eventIter.first)
				{
					activateEvent(bind, StateType(0));
				}
				break;
			}
			}
		}
	}
}

inline void EventSystem::addBinding(const Binding& binding)
{
	if (m_bindings.find(binding.m_bindName) == m_bindings.cend())
	{
		m_bindings.emplace(binding.m_bindName, binding);
	}
}

void EventSystem::activateEvent(Binding & bind, const StateType type)
{
	auto iter = m_callbacks.find(type);
	if (iter != m_callbacks.end())
	{
		auto bindIter = iter->second.find(bind.m_bindName);
		if (bindIter != iter->second.cend())
		{
			bindIter->second(&bind.m_eventDetails); 
		}
	}
}

void EventSystem::loadBindings()
{
	std::ifstream file;
	file.open(Utilities::getResourcesLocation() + "Keys.txt");
	if (!file.is_open())
	{
		std::cerr << "Failed to open: " << Utilities::getResourcesLocation() + "Keys.txt" << "\n";
	}
	std::string line;
	while (std::getline(file, line))
	{
		if (line[0] == '/') {
			continue;
		}
		std::stringstream keyStream(line);
		std::string name;
		unsigned int type;
		unsigned int code;
		keyStream >> name >> type >> code;
		EventType eventType = EventType(type);
		Binding binding(name);
		EventInfo eventInfo(code);
		binding.bindEvent(eventType, eventInfo);
		addBinding(binding);
	}
}

void EventSystem::removeCallback(const StateType type, const std::string & name)
{
	auto callbackIter = m_callbacks.find(type);
	if (callbackIter != m_callbacks.cend())
	{
		auto callBackContainerIter = callbackIter->second.find(name);
		if (callBackContainerIter != callbackIter->second.cend())
		{
			m_callbacks.erase(callbackIter);
		}
	}
}
