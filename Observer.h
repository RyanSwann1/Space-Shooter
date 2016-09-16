#pragma once

#include "Entity.h"
#include "GameEvent.h"
class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(Entity& entity, const GameEvent event) = 0;
};