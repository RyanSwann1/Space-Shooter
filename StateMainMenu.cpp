#include "StateMainMenu.h"
#include "StateManager.h"
#include "Utilities.h"


StateMainMenu::StateMainMenu(StateManager* stateManager)
	: StateBase(stateManager)
{
}

StateMainMenu::~StateMainMenu()
{
}

void StateMainMenu::onCreate()
{
	m_stateManager->getSharedContext()->m_gui->purgeEntries();
	initializeUI();

	
	EventSystem* eventSystem = m_stateManager->getSharedContext()->m_eventSystem;
	eventSystem->addCallback<StateMainMenu>(StateType::MainMenu, "Play", &StateMainMenu::reactToInput, this);
	eventSystem->addCallback<StateMainMenu>(StateType::MainMenu, "Quit", &StateMainMenu::reactToInput, this);
}

void StateMainMenu::onDestroy()
{
	EventSystem* eventSystem = m_stateManager->getSharedContext()->m_eventSystem;
	eventSystem->removeCallback(StateType::MainMenu, "Play");
	eventSystem->removeCallback(StateType::MainMenu, "Quit");
	
}

void StateMainMenu::reactToInput(EventDetails * eventDetails)
{
	if (eventDetails->m_name == "Play")
	{
		m_stateManager->switchTo(StateType::Game);
		m_stateManager->remove(StateType::MainMenu);
		
	}
	
	else if (eventDetails->m_name == "Quit")
	{
		m_stateManager->switchTo(StateType::EndGame);
		m_stateManager->remove(StateType::MainMenu);
	}
}

void StateMainMenu::initializeUI()
{
	GUI* gui = m_stateManager->getSharedContext()->m_gui;
	FontManager* fontManager = m_stateManager->getSharedContext()->m_fontManager;

	gui->addEntry("Title", new GUIEntry(fontManager, "Space Shooter", sf::Vector2f(75, 50), Utilities::getFontName(), Utilities::getTitleFontSize()));
	gui->addEntry("Play", new GUIEntry(fontManager, "(P)lay", sf::Vector2f(100, 275), Utilities::getFontName(), Utilities::getDefaultFontSize()));
	gui->addEntry("Quit", new GUIEntry(fontManager, "(Q)uit", sf::Vector2f(300, 275), Utilities::getFontName(), Utilities::getDefaultFontSize()));
}
