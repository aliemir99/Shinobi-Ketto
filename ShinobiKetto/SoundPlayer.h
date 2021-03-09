#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <list>

class SoundPlayer : private sf::NonCopyable
{
public:
	SoundPlayer();
	void						play(EffectID effect);
	void						play(EffectID effect, sf::Vector2f position);
	void						removeStoppedSounds();
	void						setListenerPosition(sf::Vector2f position);
	sf::Vector2f				getListenerPosition();

private:
	SoundBufferHolder_t		soundBuffers;
	std::list<sf::Sound>		sounds;
};


