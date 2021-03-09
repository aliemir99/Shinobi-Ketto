#pragma once
#include "State.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
class OptionsState :
	public State
{
public:
	OptionsState(StateStack& stack, Context context);

	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvents(const sf::Event& event) override;

	void					updateOptionText();

private:
	enum OptionNames
	{
		Option1,
		Option2,
		Option3,
		Exit,
	};
private:
	sf::Sprite				 backgroundSprite;
	sf::Text				 gameTitle;
	sf::Text				 menuTitle;
	std::vector<sf::Text>    mOptions;
	std::size_t              mOptionIndex;

};

