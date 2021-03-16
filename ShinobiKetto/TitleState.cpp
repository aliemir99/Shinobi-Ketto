#include "TitleState.h"

#include "State.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include <iostream>

TitleState::TitleState(StateStack& stack, Context context)
	:State(stack, context)
	, text()
	, showText(true)
	, textEffectTime(sf::Time::Zero)
	, displayStory(false)
{

	backgroundSprite.setTexture(context.textures->get(TextureID::TitleScreen));


	gameTitle.setFont(context.fonts->get(FontID::Main));
	gameTitle.setString("Shinobi Ketto");
	gameTitle.setFillColor(sf::Color::Yellow);
	centerOrigin(gameTitle);
	gameTitle.setScale(2.0f, 2.0f);
	gameTitle.setPosition(context.window->getView().getSize().x / 2, 250.f);

	text.setFont(context.fonts->get(FontID::Main));
	text.setString("Press any key to start");


	centerOrigin(text);
	text.setPosition(context.window->getView().getSize() / 2.f);

	//Story.setPosition(context.window->getView().getSize().x/2, context.window->getView().getSize().y-200);

	context.music->play(MusicID::TitleTheme);
}

void TitleState::draw()
{
	auto& window = *getContext().window;
	window.draw(backgroundSprite);
	window.draw(gameTitle);
	if (!displayStory) {
		if (showText)
			window.draw(text);
	}
	else {
		window.draw(text);
	}
		
}

bool TitleState::update(sf::Time dt)
{
	// flashing text effect
	textEffectTime += dt;
	if (!displayStory) {
		if (textEffectTime >= sf::seconds(0.5f)) {
			showText = !showText;
			textEffectTime = sf::Time::Zero;
		}
	}
	else {
		gameTitle.setPosition(gameTitle.getPosition().x, gameTitle.getPosition().y - 0.5f);
		text.setPosition(text.getPosition().x, text.getPosition().y - 0.5f);
		if(text.getPosition().y <= -1000){
			requestStackPop();
			requestStackPush(StateID::Menu);
		}
	}


	return true;
}

bool TitleState::handleEvents(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (!displayStory) {
		if (event.type == sf::Event::KeyPressed)
		{
			setupStory();
			
		}
	}
	else {
		if (event.type == sf::Event::KeyPressed)
		{
			requestStackPop();
			requestStackPush(StateID::Menu);

		}
	}
	return true;
}

void TitleState::setupStory()
{
	std::string story = ("After the death of Sensei Origami, the path of the red shinobi was set.\n\n") +
		std::string("He knew now that his only purpose in life is to revenge the murderer of master origami.\n\n")+
		std::string("He swore an oath before his leave from the Dojo Hato(Dove)\n\n") +
		std::string("The dove represents purity, gentleness, devotion, beauty, and faith.\n\n")+
		std::string("These were the pillars that made the dojo.\n\n") +
		std::string("Just as sensei Origami\'s fighting style was Pure, gentle just like the fall winds\n\n")+
		std::string("that blew through the leaves of a blossom tree.With the swing of his blade,\n\n") +
		std::string("he was able to communicate with the branches and feel their senses very clearly.\n\n\n")+
		std::string("Little did red know after the intimate argument that blue shinobi had with the master Origami.\n\n")+
		std::string("All that left was the unconscious body of the master laying on his head quarters. Red was framed.\n\n")+
		std::string("And kicked out of the Dojo.\n\n\n")+
		std::string("Upon her travels the bounty hunter has seen the unfortunate events of Dojo Hato.\n\n")+
		std::string("And decided that she would bring justice to the dojo as well as collect the bounty\n\n")+
		std::string("of the killer of Sensei Origami.\n\n")+
		std::string("But first she had to understand why the killer has taken action towards killing their master.\n\n")+
		std::string("What instinct was this shinobi following ?\n");
	Story.setString(story);
	text.setString(Story.getString());
	text.setFillColor(sf::Color::Red);
	gameTitle.setFillColor(sf::Color::Yellow);
	gameTitle.setScale(2.5f, 2.5f);
	text.setPosition(text.getPosition().x - 500, text.getPosition().y + 500);
	gameTitle.setPosition(gameTitle.getPosition().x, text.getPosition().y-200);
	displayStory = true;

}


