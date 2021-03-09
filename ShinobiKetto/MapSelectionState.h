#pragma once
#include "State.h"
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
class MapSelectionState : public State
{
public:
	MapSelectionState(StateStack& stack, Context context);
	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvents(const sf::Event& event) override;

	void					updateOptionText();

private:
	enum OptionNames
	{
		M1, // MAP 1
		M2, // MAP 2
		M3, // MAP 3
		M4, // MAP 3
		Exit,
	};

	std::map<OptionNames, std::string> backgroundFilePaths;
	std::map<OptionNames, std::string> platformFilePaths;

private:
	sf::Sprite				 backgroundSprite;
	std::vector<sf::Text>    mOptions;
	std::size_t              mOptionIndex;
	sf::Sprite				 m1Portrait;
	sf::Sprite				 m2Portrait;
	sf::Sprite				 m3Portrait;
	sf::Sprite				 m4Portrait;
	sf::Texture				 m1PortraitTexture;
	sf::Texture				 m2PortraitTexture;
	sf::Texture				 m3PortraitTexture;
	sf::Texture				 m4PortraitTexture;
	sf::Text				 menuTitle;
};

