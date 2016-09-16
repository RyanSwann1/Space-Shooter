#pragma once

#include <SFML\Audio.hpp>
#include "SoundManager.h"
#include <string>

class Audio
{
public:
	Audio(SoundManager& soundManager, const std::string& audioClipName);

	void play() { m_audioClip.play(); }
	void stop() { m_audioClip.stop(); }
	std::string getAudioClipName() const { return m_audioClipName; }
	sf::Sound getAudioClip() const { return m_audioClip; }

private:
	sf::Sound m_audioClip;
	std::string m_audioClipName;
	SoundManager m_soundManager;
};

