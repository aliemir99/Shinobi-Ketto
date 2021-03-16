#pragma once
#include "State.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvents(const sf::Event& event) override;

	void					setupStory();

private:
	sf::Sprite				backgroundSprite;
	sf::Text				text;
	sf::Text				Story;
	sf::Text				gameTitle;

	bool					showText;
	bool					displayStory;
	sf::Time				textEffectTime;
};


