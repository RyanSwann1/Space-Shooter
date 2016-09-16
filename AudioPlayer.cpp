#include "AudioPlayer.h"
#include <iostream>



AudioPlayer::AudioPlayer()
{
}

AudioPlayer::~AudioPlayer()
{
	purgeAudioClips();
}

void AudioPlayer::addAudioClip(const std::string& id, Audio* audioClip)
{
	auto iter = m_audioClips.find(id);
	if (iter == m_audioClips.cend())
	{
		m_audioClips[id] = audioClip;
	}
	else
	{
		std::cerr << id << " already exists." << "\n";
	}
}

void AudioPlayer::playAudioClip(const std::string & id)
{
	auto iter = m_audioClips.find(id);
	if (iter != m_audioClips.cend())
	{
		iter->second->play();
	}
}

void AudioPlayer::stopAudioClip(const std::string & id)
{
	auto iter = m_audioClips.find(id);
	if (iter != m_audioClips.cend())
	{
		iter->second->stop();
	}
}

void AudioPlayer::purgeAudioClips()
{
	for (auto &i : m_audioClips)
	{
		delete i.second;
		i.second = nullptr;
	}
	m_audioClips.clear();
}

sf::Sound AudioPlayer::getAudioClip(const std::string & id) const
{
	auto iter = m_audioClips.find(id);
	if (iter != m_audioClips.cend())
	{
		return iter->second->getAudioClip();
	}
}
