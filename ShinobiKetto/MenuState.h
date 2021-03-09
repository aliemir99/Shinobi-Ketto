#pragma once
#include "State.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvents(const sf::Event& event) override;

	void					updateOptionText();

private:
	enum OptionNames
	{
		Play,
		Options,
		HowToPlay,
		Exit,
	};
private:
	sf::Sprite				 backgroundSprite;
	sf::Text				 gameTitle;
	std::vector<sf::Text>    mOptions;
	std::size_t              mOptionIndex;

};

