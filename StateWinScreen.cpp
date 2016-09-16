#include "StateWinScreen.h"
#include "FontManager.h"
#include "Utilities.h"
#include "StateManager.h"


StateWinScreen::StateWinScreen(StateManager* stateManager)
	:StateBase(stateManager)
{
}


StateWinScreen::~StateWinScreen()
{
}

void StateWinScreen::onCreate()
{

}

void StateWinScreen::update(const float deltaTime)
{
	m_stateManager->getSharedContext()->m_gui->purgeEntries();
	initializeUI();

	m_stateManager->getSharedContext()->m_eventSystem->addCallback<StateWinScreen>(StateType::WinScreen, std::string("MainMenu"), &StateWinScreen::reactToInput, this);

}

void StateWinScreen::draw(sf::RenderWindow & window)
{
}

void StateWinScreen::reactToInput(EventDetails * eventDetails)
{
	if (eventDetails->m_name == "MainMenu")
	{
		m_stateManager->switchTo(StateType::MainMenu);
		m_stateManager->remove(StateType::WinScreen);
	}
}

void StateWinScreen::initializeUI()
{
	FontManager* fontManager = m_stateManager->getSharedContext()->m_fontManager;
	GUI* gui = m_stateManager->getSharedContext()->m_gui;
	gui->addEntry(std::string("TitleText"), new GUIEntry(fontManager, std::string("You Win"), sf::Vector2f(150, 50), Utilities::getFontName(), Utilities::getTitleFontSize()));
	gui->addEntry(std::string("MainMenuText"), new GUIEntry(fontManager, std::string("(M)ain Menu"), sf::Vector2f(175, 250), Utilities::getFontName(), Utilities::getDefaultFontSize()));
}
