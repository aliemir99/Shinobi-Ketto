#pragma once

#include "World.h"
#include "Player.h"
#include "State.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void			draw() override;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvents(const sf::Event& event) override;

private:
	World					world;
	Player& player;
	sf::Text				roundOverText;

};


