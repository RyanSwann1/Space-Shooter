#include "GameManager.h"
#include "SharedContext.h"
#include "StateManager.h"
#include <iostream>


GameManager::GameManager(SharedContext* sharedContext)
	:m_sharedContext(sharedContext),
	m_gameOngoing(true)
{
}

GameManager::~GameManager()
{
}

void GameManager::onNotify(Entity & entity, const GameEvent event)
{
	switch (event)
	{
	case (GameEvent::Game_Won) :
	{
		if (entity.getType() == EntityType::Player && m_gameOngoing)
		{
			m_sharedContext->m_stateManager->switchTo(StateType::WinScreen);
			m_sharedContext->m_stateManager->remove(StateType::Game);
		}
		break;
	}
	case (GameEvent::Player_Dead) :
	{
		if (entity.getType() == EntityType::Player && m_gameOngoing)
		{
			//Switch to Death screen state
			m_sharedContext->m_stateManager->switchTo(StateType::DeathScreen);
			m_sharedContext->m_stateManager->remove(StateType::Game);
			m_gameOngoing = false;
		}
		break;
	}
	}
}

