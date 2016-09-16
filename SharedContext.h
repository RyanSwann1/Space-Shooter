#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H

#include "Window.h"
#include "EventSystem.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "GUI.h"
class EntityManager;
class StateManager;
struct SharedContext
{
	SharedContext() :
		m_stateManager(nullptr),
		m_window(nullptr),
		m_eventSystem(nullptr),
		m_entityManager(nullptr),
		m_textureManager(nullptr),
		m_fontManager(nullptr),
		m_gui(nullptr),
		m_soundManager(nullptr) {}

	Window* m_window;
	StateManager* m_stateManager;
	EntityManager* m_entityManager;
	SoundManager* m_soundManager;
	EventSystem* m_eventSystem;
	TextureManager* m_textureManager;
	FontManager* m_fontManager;
	GUI* m_gui;
};
#endif // !SHARED_CONTEXT_H

