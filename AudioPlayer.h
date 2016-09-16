#pragma once

#include "Audio.h"
#include <unordered_map>
#include <string>
class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();

	void addAudioClip(const std::string& id, Audio* audio);
	void playAudioClip(const std::string& id);
	void stopAudioClip(const std::string& id);
	void purgeAudioClips();

	sf::Sound getAudioClip(const std::string& id) const;

private:
	std::unordered_map<std::string, Audio*> m_audioClips;
};

