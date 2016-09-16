#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "StateType.h"
#include <SFML\Window.hpp>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

enum class EventType
{
	
	KeyPressed = sf::Event::KeyPressed,
	KeyReleased = sf::Event::KeyReleased,
	Closed = sf::Event::Closed
};

struct EventInfo
{
	EventInfo()
		:m_code(0) {}
	EventInfo(int code)
		: m_code(code) {}
	
	int m_code; 
};

struct EventDetails
{
	EventDetails(const std::string& name)
		: m_name(name) {}

	std::string m_name;
};

struct Binding
{
	Binding(const std::string& bindName)
		:m_bindName(bindName),
		m_eventDetails(bindName) {}

	void bindEvent(const EventType type, EventInfo info = EventInfo())
	{
		m_events.emplace_back(type, info);
	}
	
	EventDetails m_eventDetails;
	std::vector<std::pair<EventType, EventInfo>> m_events;
	std::string m_bindName;
};

struct SharedContext;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using namespace std::placeholders;
class EventSystem
{
public:
	EventSystem(SharedContext* sharedContext);
	~EventSystem();

	void setCurrentState(const StateType state) { m_stateCurrent = state; }
	void setFocus(const bool focus) { m_hasFocus = focus; }
	void update(sf::Event sfmlEvent);
	void loadBindings();
	void removeCallback(const StateType type, const std::string& name);
	inline void addBinding(const Binding& binding);

	//Cannot allow more than one callback at teh same time
	template <class T>
	bool addCallback(const StateType stateType, const std::string& name, void(T::*func)(EventDetails*), T* instance)
	{
		auto iter = m_callbacks.emplace(stateType, CallbackContainer()).first; //Get iterator of newly added callback
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return iter->second.emplace(name, temp).second;
	}

	

private:
	bool m_hasFocus;
	std::unordered_map<std::string, Binding> m_bindings;
	std::unordered_map<StateType, CallbackContainer> m_callbacks;
	StateType m_stateCurrent;
	SharedContext* m_sharedContext;

	void activateEvent(Binding& bind, const StateType type);
};
#endif // !EVENT_SYSTEM_H