#include "OptionsState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "MusicPlayer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
OptionsState::OptionsState(StateStack& stack, Context context)
	:State(stack, context)
	, mOptionIndex(0)
	, mOptions()
{
	sf::Font& font = context.fonts->get(FontID::Main);

	backgroundSprite.setTexture(context.textures->get(TextureID::OptionsScreen));

	gameTitle.setFont(context.fonts->get(FontID::Main));
	gameTitle.setString("Shinobi Ketto");
	gameTitle.setFillColor(sf::Color::Yellow);
	centerOrigin(gameTitle);
	gameTitle.setScale(2.0f, 2.0f);
	gameTitle.setPosition(context.window->getView().getSize().x / 2, 250.f);

	menuTitle.setFont(context.fonts->get(FontID::Main));
	menuTitle.setString("Options");
	menuTitle.setFillColor(sf::Color::Black);
	centerOrigin(menuTitle);
	menuTitle.setScale(2.0f, 2.0f);
	menuTitle.setPosition(gameTitle.getPosition().x, gameTitle.getPosition().y + 100);

	sf::Text option1;
	option1.setFont(font);
	option1.setString("Option 1");
	centerOrigin(option1);
	option1.setPosition(context.window->getView().getSize() / 2.f);
	mOptions.push_back(option1);

	sf::Text option2;
	option2.setFont(font);
	option2.setString("Option 2");
	centerOrigin(option2);
	option2.setPosition(option1.getPosition() + sf::Vector2f(0.f, 50.f));
	mOptions.push_back(option2);

	sf::Text option3;
	option3.setFont(font);
	option3.setString("Option 3");
	centerOrigin(option3);
	option3.setPosition(option2.getPosition() + sf::Vector2f(0.f, 50.f));
	mOptions.push_back(option3);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Back");
	centerOrigin(exitOption);
	exitOption.setPosition(option3.getPosition() + sf::Vector2f(0.f, 50.f));
	mOptions.push_back(exitOption);

	updateOptionText();

	//context.music->play(MusicID::MenuTheme);
}

void OptionsState::draw()
{
	auto& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);
	window.draw(gameTitle);
	window.draw(menuTitle);

	for (const auto& text : mOptions) {
		window.draw(text);
	}
}

bool OptionsState::update(sf::Time dt)
{
	return false;
}

bool OptionsState::handleEvents(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (mOptionIndex == Option1) {
			requestStackPop();
		}
		else if (mOptionIndex == Option2) {
			requestStackPop();
		}
		else if (mOptionIndex == Option3) {
			requestStackPop();

		}
		else if (mOptionIndex == Exit) {
			requestStackPop();
			requestStackPush(StateID::Menu);
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

void OptionsState::updateOptionText()
{
	if (mOptions.empty())
		return;
	for (auto& text : mOptions) {
		text.setFillColor(sf::Color::White);
	}
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}
