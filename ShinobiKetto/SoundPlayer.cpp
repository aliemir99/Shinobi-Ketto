#include "SoundPlayer.h"
#include <cmath>
#include <SFML/Audio/Listener.hpp>
namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D =
		std::sqrt(MinDistance2D * MinDistance2D
			+ ListenerZ * ListenerZ);
}

SoundPlayer::SoundPlayer()
	: soundBuffers()
	, sounds()
{
	soundBuffers.load(EffectID::GongHit, "Media/Sound/gong-hit.wav");
	soundBuffers.load(EffectID::GongRoll, "Media/Sound/gong-roll.wav");
	soundBuffers.load(EffectID::H1Attack1, "Media/Sound/redAttack1.wav");
	soundBuffers.load(EffectID::H1Attack2, "Media/Sound/redAttack2.wav");
	soundBuffers.load(EffectID::H1GetHit, "Media/Sound/redGetHit.wav");
	soundBuffers.load(EffectID::H2Attack1, "Media/Sound/blueAttack1.wav");
	soundBuffers.load(EffectID::H2Attack2, "Media/Sound/blueAttack2.wav");
	soundBuffers.load(EffectID::H2GetHit, "Media/Sound/blueGetHit.wav");
	soundBuffers.load(EffectID::H3Attack1, "Media/Sound/girlAttack1.wav");
	soundBuffers.load(EffectID::H3Attack2, "Media/Sound/girlAttack2.wav");
	soundBuffers.load(EffectID::H3GetHit, "Media/Sound/girlGetHit.wav");
	soundBuffers.load(EffectID::TakeDamage, "Media/Sound/takeDamage.wav");
	soundBuffers.load(EffectID::MissAttack, "Media/Sound/missAttack.wav");
	// Listener points towards the screen (default in SFML)
	sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(EffectID effect)
{
	play(effect, getListenerPosition());

}

void SoundPlayer::play(EffectID effect, sf::Vector2f position)
{
	sounds.push_back(sf::Sound());
	sf::Sound& sound = sounds.back();
	sound.setLoop(false);
	sound.setBuffer(soundBuffers.get(effect));
	sound.setPosition(position.x, -position.y, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);
	sound.play();


}




void SoundPlayer::removeStoppedSounds()
{

	sounds.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
	sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListenerPosition()
{
	auto pos = sf::Listener::getPosition();
	return  sf::Vector2f(pos.x, pos.y);
}
