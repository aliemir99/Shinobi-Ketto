#include "TitleState.h"

#include "State.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"
#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
	:State(stack, context)
	, text()
	, showText(true)
	, textEffectTime(sf::Time::Zero)
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


	context.music->play(MusicID::TitleTheme);
}

void TitleState::draw()
{
	auto& window = *getContext().window;
	window.draw(backgroundSprite);
	window.draw(gameTitle);
	if (showText)
		window.draw(text);
}

bool TitleState::update(sf::Time dt)
{
	// flashing text effect
	textEffectTime += dt;
	if (textEffectTime >= sf::seconds(0.5f)) {
		showText = !showText;
		textEffectTime = sf::Time::Zero;
	}
	return true;
}

bool TitleState::handleEvents(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(StateID::Menu);
	}
	return true;
}


