#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include <map>
#include <string>

class MusicPlayer : private sf::NonCopyable
{
public:
	enum class MUSIC_TYPE {
		JUNGLE,
		FOREST,
		LAKE,
		COUNTY
	};

	MusicPlayer();

	void								play(MusicID theme);
	void								stop();

	void								setPaused(bool paused);
	void								setVolume(float vol);

	MUSIC_TYPE							getType();
	void								setMusicType(MUSIC_TYPE type);
private:
	MUSIC_TYPE							musicType;
	sf::Music							music;
	std::map<MusicID, std::string>		filenames;
	float								volume;


};


