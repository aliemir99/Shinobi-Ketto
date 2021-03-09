#pragma once
#include "State.h"
#include "Actor.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
class CharacterSelectionState : public State
{
public:
	Actor::Type p1Char;
	Actor::Type p2Char;
	CharacterSelectionState(StateStack& stack, Context context);

	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvents(const sf::Event& event) override;

	void					updateOptionText();

private:
	enum OptionNames
	{
		C1, // CHARACTER 1
		C2, // CHARACTER 2
		C3, // CHARACTER 3
		Exit,
	};
	std::map<OptionNames, std::string> hudLeftFilePaths;
	std::map<OptionNames, std::string> hudRightFilePaths;
private:
	sf::Sprite				 backgroundSprite;
	sf::Sprite				 c1Portrait;
	sf::Sprite				 c2Portrait;
	sf::Sprite				 c3Portrait;
	sf::Texture				 c1PortraitTexture;
	sf::Texture				 c2PortraitTexture;
	sf::Texture				 c3PortraitTexture;
	std::vector<sf::Text>    mOptions;
	std::size_t              mOptionIndex;
	int						 selectionCount;
	sf::Text				 menuTitle;
	//sf::Text				 versusText;

	sf::Text				 p1Selection;
	sf::Text				 p2Selection;

	sf::Sprite				p1SelectedChar;
	sf::Sprite				p2SelectedChar;
};




