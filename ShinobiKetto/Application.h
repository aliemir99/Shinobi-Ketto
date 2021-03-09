#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "StateStack.h"
#include "Player.h"

#include "MusicPlayer.h"
#include "SoundPlayer.h"

class Application
{
public:
	Application();
	void					run();

private:
	void					processInput();
	void					update(sf::Time dt);
	void					render();

	void					updateStatistics(sf::Time et);

	void					registerStates();

private:
	static const sf::Time	TimePerFrame;

	//context
	sf::RenderWindow		window;
	TextureHolder_t         textures;
	FontHolder_t			fonts;
	Player					player;
	MusicPlayer				music;
	SoundPlayer				sounds;

	StateStack				stateStack;

	sf::Text				statsText;
	sf::Time				statsUpdateTime;
	std::size_t				statsNumFrames;

	Actor::Type				p1Char;
	Actor::Type				p2Char;
	std::string				backGroundFilePath;
	std::string				platformFilePath;
	std::string				hudLeftFilePath;
	std::string				hudRightFilePath;
};

