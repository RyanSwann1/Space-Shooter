#include "Audio.h"



Audio::Audio(SoundManager& soundManager, const std::string& audioClipName) 
	: m_soundManager(soundManager),
	m_audioClipName(audioClipName)
{
	if (soundManager.requireResource(m_audioClipName))
	{
		m_audioClip.setBuffer(*soundManager.getResource(m_audioClipName));
	}
}
