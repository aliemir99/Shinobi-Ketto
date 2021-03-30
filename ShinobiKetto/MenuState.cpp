#include "MenuState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
MenuState::MenuState(StateStack& stack, Context context)
	:State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{

	sf::Font& font = context.fonts->get(FontID::Main);

	backgroundSprite.setTexture(context.textures->get(TextureID::MenuScreen));

	gameTitle.setFont(context.fonts->get(FontID::Main));
	gameTitle.setString("Shinobi Ketto");
	gameTitle.setFillColor(sf::Color::Yellow);
	centerOrigin(gameTitle);
	gameTitle.setScale(2.0f, 2.0f);
	gameTitle.setPosition(context.window->getView().getSize().x / 2, 250.f);


	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text optionsOption;
	optionsOption.setFont(font);
	optionsOption.setString("Options");
	centerOrigin(optionsOption);
	optionsOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 50.f));
	mOptions.push_back(optionsOption);

	sf::Text howToPlayOption;
	howToPlayOption.setFont(font);
	howToPlayOption.setString("How To Play");
	centerOrigin(howToPlayOption);
	howToPlayOption.setPosition(optionsOption.getPosition() + sf::Vector2f(0.f, 50.f));
	mOptions.push_back(howToPlayOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(howToPlayOption.getPosition() + sf::Vector2f(0.f, 50.f));
	mOptions.push_back(exitOption);

	updateOptionText();

	context.music->play(MusicID::MenuTheme);
}

void MenuState::draw()
{
	auto& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(gameTitle);

	for (const auto& text : mOptions) {
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt)
{
	return false;
}

bool MenuState::handleEvents(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Play) {
			requestStackPop();
			requestStackPush(StateID::CharacterSelection);
		}
		else if (mOptionIndex == Options) {
			requestStackPop();
			requestStackPush(StateID::Options);
		}
		else if (mOptionIndex == HowToPlay) {
			requestStackPop();
			requestStackPush(StateID::HowToPlay);
		}
		else if (mOptionIndex == Exit) {
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up) {
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down) {
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}

	return false;
}

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;
	for (auto& text : mOptions) {
		text.setFillColor(sf::Color::White);
	}
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}
