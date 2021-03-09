#include "RoundOverState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
RoundOverState::RoundOverState(StateStack& stack, Context context)
	: State(stack, context)
	, backgroundSprite()
	, roundOverText()
	, instructionText()
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();
	roundOverText.setFont(font);
	roundOverText.setString("Round Won! Congrats");
	roundOverText.setCharacterSize(70);
	centerOrigin(roundOverText);
	roundOverText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);
	instructionText.setFont(font);
	instructionText.setString("(Press any key to start next round)");
	centerOrigin(instructionText);
	instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}
void RoundOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());
	window.draw(backgroundShape);
	window.draw(roundOverText);
	window.draw(instructionText);
}

bool RoundOverState::update(sf::Time dt)
{
	return false;
}

bool RoundOverState::handleEvents(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}
	if (event.key.code == sf::Keyboard::Backspace)
	{
		requestStackPop();
	}
	if (event.key.code == sf::Keyboard::Enter)
	{
		requestStackPop();
	}
	return false;
}