#include "Window.h"
#include "SharedContext.h"
#include <iostream>

Window::Window(SharedContext* sharedContext)
	: m_eventSystem(sharedContext)
{
	setup(sf::Vector2u(480, 640), "SFML_GAME");
}

Window::Window(SharedContext * sharedContext, const sf::Vector2u & windowSize, const std::string & windowTitle)
	: m_eventSystem(sharedContext)
{
	
	setup(windowSize, windowTitle);
}


Window::~Window()
{
}

void Window::setup(const sf::Vector2u & windowSize, const std::string & windowTitle)
{
	m_windowSize = windowSize;
	m_windowTitle = windowTitle;
	m_fullscreen = false;
	m_hasFocus = false;
	create();
}

inline void Window::toggleFullScreen(const bool fullScreen)
{
	fullScreen ? m_fullscreen : m_fullscreen = false;	
}

void Window::update()
{
	sf::Event sfmlEvent;
	//While polling individual events
	while (m_window.pollEvent(sfmlEvent))
	{
		if (sfmlEvent.type == sf::Event::EventType::LostFocus) 
		{
			m_hasFocus = false;
			m_eventSystem.setFocus(false);
		}
		else if (sfmlEvent.type == sf::Event::EventType::GainedFocus)
		{
			m_hasFocus = true;
			m_eventSystem.setFocus(true);
		}
		else if (sfmlEvent.type == sf::Event::EventType::Closed) {
			close();
		}
		
		m_eventSystem.update(sfmlEvent);
	}
	
}

void Window::draw(sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::create()
{
	auto style = (m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
}

void Window::reactToInput(const EventDetails * eventDetails)
{

}

inline void Window::saySomething()
{
	std::cout << "Player Moves Left." << "\n";
}

inline void Window::saySomethingElse()
{
	std::cout << "Player moves right." << "\n";
}
