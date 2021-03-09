#include "DataTables.h"
#include "JsonFrameParser.h"

std::map<Actor::Type, ActorData> initializeActorData()
{
	std::map<Actor::Type, ActorData> data;
	//FIGHTING GAME TEXTURE ASSIGNING
	data[Actor::Type::Hero1].texture = TextureID::Hero1;
	data[Actor::Type::Hero2].texture = TextureID::Hero2;
	data[Actor::Type::Hero3].texture = TextureID::Hero3;
	data[Actor::Type::Platform].texture = TextureID::platform;
	JsonFrameParser hero1 = JsonFrameParser("Media/Textures/Fight/hero1.json");

	data[Actor::Type::Hero1].animations[Actor::State::Idle].addFrameSet(hero1.getFramesFor("Idle"));
	data[Actor::Type::Hero1].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero1].animations[Actor::State::Idle].setRepeating(true);


	data[Actor::Type::Hero1].animations[Actor::State::Attack1].addFrameSet(hero1.getFramesFor("Attack1"));
	data[Actor::Type::Hero1].animations[Actor::State::Attack1].setDuration(sf::seconds(1.0f));
	data[Actor::Type::Hero1].animations[Actor::State::Attack1].setRepeating(false);


	data[Actor::Type::Hero1].animations[Actor::State::Attack2].addFrameSet(hero1.getFramesFor("Attack2"));
	data[Actor::Type::Hero1].animations[Actor::State::Attack2].setDuration(sf::seconds(0.5f));
	data[Actor::Type::Hero1].animations[Actor::State::Attack2].setRepeating(false);


	data[Actor::Type::Hero1].animations[Actor::State::Dead].addFrameSet(hero1.getFramesFor("Death"));
	data[Actor::Type::Hero1].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero1].animations[Actor::State::Dead].setRepeating(false);


	data[Actor::Type::Hero1].animations[Actor::State::Fall].addFrameSet(hero1.getFramesFor("Fall"));
	data[Actor::Type::Hero1].animations[Actor::State::Fall].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero1].animations[Actor::State::Fall].setRepeating(false);


	data[Actor::Type::Hero1].animations[Actor::State::Jump].addFrameSet(hero1.getFramesFor("Jump"));
	data[Actor::Type::Hero1].animations[Actor::State::Jump].setDuration(sf::seconds(0.3f));
	data[Actor::Type::Hero1].animations[Actor::State::Jump].setRepeating(false);

	data[Actor::Type::Hero1].animations[Actor::State::Run].addFrameSet(hero1.getFramesFor("Run"));
	data[Actor::Type::Hero1].animations[Actor::State::Run].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero1].animations[Actor::State::Run].setRepeating(false);

	data[Actor::Type::Hero1].animations[Actor::State::TakeHit].addFrameSet(hero1.getFramesFor("Take Hit"));
	data[Actor::Type::Hero1].animations[Actor::State::TakeHit].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero1].animations[Actor::State::TakeHit].setRepeating(false);



	JsonFrameParser hero2 = JsonFrameParser("Media/Textures/Fight/hero2.json");

	data[Actor::Type::Hero2].animations[Actor::State::Idle].addFrameSet(hero2.getFramesFor("Idle"));
	data[Actor::Type::Hero2].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Idle].setRepeating(true);


	data[Actor::Type::Hero2].animations[Actor::State::Attack1].addFrameSet(hero2.getFramesFor("Attack1"));
	data[Actor::Type::Hero2].animations[Actor::State::Attack1].setDuration(sf::seconds(0.6f));
	data[Actor::Type::Hero2].animations[Actor::State::Attack1].setRepeating(false);


	data[Actor::Type::Hero2].animations[Actor::State::Attack2].addFrameSet(hero2.getFramesFor("Attack2"));
	data[Actor::Type::Hero2].animations[Actor::State::Attack2].setDuration(sf::seconds(0.4f));
	data[Actor::Type::Hero2].animations[Actor::State::Attack2].setRepeating(false);


	data[Actor::Type::Hero2].animations[Actor::State::Dead].addFrameSet(hero2.getFramesFor("Death"));
	data[Actor::Type::Hero2].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Dead].setRepeating(false);


	data[Actor::Type::Hero2].animations[Actor::State::Fall].addFrameSet(hero2.getFramesFor("Fall"));
	data[Actor::Type::Hero2].animations[Actor::State::Fall].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Fall].setRepeating(false);


	data[Actor::Type::Hero2].animations[Actor::State::Jump].addFrameSet(hero2.getFramesFor("Jump"));
	data[Actor::Type::Hero2].animations[Actor::State::Jump].setDuration(sf::seconds(0.3f));
	data[Actor::Type::Hero2].animations[Actor::State::Jump].setRepeating(false);

	data[Actor::Type::Hero2].animations[Actor::State::Run].addFrameSet(hero2.getFramesFor("Run"));
	data[Actor::Type::Hero2].animations[Actor::State::Run].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Run].setRepeating(false);

	data[Actor::Type::Hero2].animations[Actor::State::TakeHit].addFrameSet(hero2.getFramesFor("Take hit"));
	data[Actor::Type::Hero2].animations[Actor::State::TakeHit].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::TakeHit].setRepeating(false);

	JsonFrameParser hero3 = JsonFrameParser("Media/Textures/Fight/hero3.json");

	data[Actor::Type::Hero3].animations[Actor::State::Idle].addFrameSet(hero3.getFramesFor("Idle"));
	data[Actor::Type::Hero3].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero3].animations[Actor::State::Idle].setRepeating(true);


	data[Actor::Type::Hero3].animations[Actor::State::Attack1].addFrameSet(hero3.getFramesFor("Attack1"));
	data[Actor::Type::Hero3].animations[Actor::State::Attack1].setDuration(sf::seconds(0.3f));
	data[Actor::Type::Hero3].animations[Actor::State::Attack1].setRepeating(false);


	data[Actor::Type::Hero3].animations[Actor::State::Attack2].addFrameSet(hero3.getFramesFor("Attack2"));
	data[Actor::Type::Hero3].animations[Actor::State::Attack2].setDuration(sf::seconds(0.8f));
	data[Actor::Type::Hero3].animations[Actor::State::Attack2].setRepeating(false);


	data[Actor::Type::Hero3].animations[Actor::State::Dead].addFrameSet(hero3.getFramesFor("Death"));
	data[Actor::Type::Hero3].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero3].animations[Actor::State::Dead].setRepeating(false);


	data[Actor::Type::Hero3].animations[Actor::State::Fall].addFrameSet(hero3.getFramesFor("Fall"));
	data[Actor::Type::Hero3].animations[Actor::State::Fall].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero3].animations[Actor::State::Fall].setRepeating(false);


	data[Actor::Type::Hero3].animations[Actor::State::Jump].addFrameSet(hero3.getFramesFor("Jump"));
	data[Actor::Type::Hero3].animations[Actor::State::Jump].setDuration(sf::seconds(0.3f));
	data[Actor::Type::Hero3].animations[Actor::State::Jump].setRepeating(false);

	data[Actor::Type::Hero3].animations[Actor::State::Run].addFrameSet(hero3.getFramesFor("Run"));
	data[Actor::Type::Hero3].animations[Actor::State::Run].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero3].animations[Actor::State::Run].setRepeating(false);

	data[Actor::Type::Hero3].animations[Actor::State::TakeHit].addFrameSet(hero3.getFramesFor("Take Hit"));
	data[Actor::Type::Hero3].animations[Actor::State::TakeHit].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero3].animations[Actor::State::TakeHit].setRepeating(false);


	return data;
}