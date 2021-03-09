#include "HowToPlayState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
HowToPlayState::HowToPlayState(StateStack& stack, Context context)
	:State(stack, context)
	, mOptionIndex(0)
	, mOptions()
{
	sf::Font& font = context.fonts->get(FontID::Main);

	backgroundSprite.setTexture(context.textures->get(TextureID::HowToPlayScreen));


	p1Controls.setTexture(context.textures->get(TextureID::p1Controls));
	p1Controls.setPosition(300.f, 400.f);

	p2Controls.setTexture(context.textures->get(TextureID::p2Controls));
	p2Controls.setPosition(1420.f, 400.f);

	gameTitle.setFont(context.fonts->get(FontID::Main));
	gameTitle.setString("Shinobi Ketto");
	gameTitle.setFillColor(sf::Color::Yellow);
	centerOrigin(gameTitle);
	gameTitle.setScale(2.0f, 2.0f);
	gameTitle.setPosition(context.window->getView().getSize().x / 2, 250.f);

	menuTitle.setFont(context.fonts->get(FontID::Main));
	menuTitle.setString("How To Play");
	menuTitle.setFillColor(sf::Color::Black);
	centerOrigin(menuTitle);
	menuTitle.setScale(2.0f, 2.0f);
	menuTitle.setPosition(gameTitle.getPosition().x, gameTitle.getPosition().y + 100);

	player1Text.setFont(font);
	player1Text.setString("Player 1");
	player1Text.setFillColor(sf::Color::Black);
	centerOrigin(player1Text);
	player1Text.setPosition(420.f, 400.f);


	player2Text.setFont(font);
	player2Text.setFillColor(sf::Color::Black);
	player2Text.setString("Player 2");
	centerOrigin(player2Text);
	player2Text.setPosition(1545.f, 400.f);


	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Back");
	centerOrigin(exitOption);
	exitOption.setPosition(menuTitle.getPosition().x, menuTitle.getPosition().y + 300);
	mOptions.push_back(exitOption);

	updateOptionText();

}


void HowToPlayState::draw()
{
	auto& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(gameTitle);
	window.draw(menuTitle);
	window.draw(p1Controls);
	window.draw(p2Controls);
	window.draw(player1Text);
	window.draw(player2Text);

	for (const auto& text : mOptions) {
		window.draw(text);
	}
}

bool HowToPlayState::update(sf::Time dt)
{
	return false;
}

bool HowToPlayState::handleEvents(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{


		requestStackPop();
		requestStackPush(StateID::Menu);

	}

	return false;
}

void HowToPlayState::updateOptionText()
{
	if (mOptions.empty())
		return;
	for (auto& text : mOptions) {
		text.setFillColor(sf::Color::White);
	}
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}
