#include "StateDeathScreen.h"
#include "StateManager.h"
#include "FontManager.h"
#include "Utilities.h"

StateDeathScreen::StateDeathScreen(StateManager* stateManager)
	: StateBase(stateManager)
{
}


StateDeathScreen::~StateDeathScreen()
{
}

void StateDeathScreen::onCreate()
{
	m_stateManager->getSharedContext()->m_gui->purgeEntries();
	initializeUI();

	EventSystem* eventSystem = m_stateManager->getSharedContext()->m_eventSystem;
	eventSystem->addCallback<StateDeathScreen>(StateType::DeathScreen, "Retry", &StateDeathScreen::reactToInput, this);
	eventSystem->addCallback<StateDeathScreen>(StateType::DeathScreen, "MainMenu", &StateDeathScreen::reactToInput, this); 
}

void StateDeathScreen::onDestroy()
{
	
}

void StateDeathScreen::onEnter()
{
	std::cout << "Entered teh Death screen." << "\n";
}


void StateDeathScreen::onExit()
{
}

void StateDeathScreen::update(const float deltaTime)
{
}

void StateDeathScreen::draw(sf::RenderWindow & window)
{
}

void StateDeathScreen::reactToInput(EventDetails * eventDetails)
{
	if (eventDetails->m_name == "Retry")
	{
		m_stateManager->switchTo(StateType::Game);
		m_stateManager->remove(StateType::DeathScreen);
	}
	else if(eventDetails->m_name == "MainMenu")
	{
		m_stateManager->switchTo(StateType::MainMenu);
		m_stateManager->remove(StateType::DeathScreen);
	}
}

void StateDeathScreen::initializeUI()
{
	FontManager* fontManager = m_stateManager->getSharedContext()->m_fontManager;
	GUI* gui = m_stateManager->getSharedContext()->m_gui;
	gui->addEntry(std::string("TitleText"), new GUIEntry(fontManager, std::string("You Died"), sf::Vector2f(150, 50), Utilities::getFontName(), Utilities::getTitleFontSize()));
	gui->addEntry(std::string("MainMenuText"), new GUIEntry(fontManager, std::string("(M)ain Menu"), sf::Vector2f(100, 250), Utilities::getFontName(), Utilities::getDefaultFontSize()));
	gui->addEntry(std::string("RetryText"), new GUIEntry(fontManager, std::string("(R)etry"), sf::Vector2f(300, 250), Utilities::getFontName(), Utilities::getDefaultFontSize()));
}
