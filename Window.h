#ifndef WINDOW_H
#define WINDOW_H

#include "EventSystem.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>

struct SharedContext;
class Window
{
	friend class Game;
public:
	Window(SharedContext* sharedContext);
	Window(SharedContext* sharedContext, const sf::Vector2u& windowSize, const std::string& windowTitle);
	~Window();

	void beginDraw() { m_window.clear(sf::Color::Black); }
	void endDraw() { m_window.display(); }
	bool isRunning() const { return m_window.isOpen(); }
	inline void toggleFullScreen(const bool fullScreen);
	void update();
	void draw(sf::Drawable& drawable);
	void close() { m_window.close(); }

	EventSystem* getEventSystem() { return &m_eventSystem; }
	sf::Vector2u getSize() const { return m_windowSize; }
	sf::RenderWindow& getWindow() { return m_window; }

private:
	sf::RenderWindow m_window;
	EventSystem m_eventSystem;
	bool m_hasFocus;
	bool m_fullscreen;
	std::string m_windowTitle;
	sf::Vector2u m_windowSize;

	void setup(const sf::Vector2u& windowSize, const std::string& windowTitle);
	void create();
	
	void reactToInput(const EventDetails* eventDetails);
	inline void saySomething();
	inline void saySomethingElse();
	
};
#endif // !WINDOW_H