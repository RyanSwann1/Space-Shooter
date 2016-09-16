#include "StateEndGame.h"
#include "StateManager.h"


StateEndGame::StateEndGame(StateManager* stateManager)
	: StateBase(stateManager)
{
}


StateEndGame::~StateEndGame()
{
}

void StateEndGame::onEnter()
{
	m_stateManager->getSharedContext()->m_window->close();

}
