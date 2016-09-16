#pragma once
#include "Observer.h"

struct SharedContext;
class Game;
class GameManager :
	public Observer
{
public:
	GameManager(SharedContext* sharedContext);
	~GameManager();

	void onNotify(Entity& entity, const GameEvent event) override;

private:
	SharedContext* m_sharedContext;
	bool m_gameOngoing;

};

