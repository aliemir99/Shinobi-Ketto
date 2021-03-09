#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, Context context)
	:stack(&stack)
	, context(context)
{
}

State::~State()
{
}

void State::requestStackPush(StateID stateID)
{
	stack->pushState(stateID);
}

void State::requestStackPop()
{
	stack->popState();
}

void State::requestStackClear()
{
	stack->clearStates();
}

State::Context State::getContext()
{
	return context;
}

State::Context::Context(sf::RenderWindow& window, TextureHolder_t& textures,
	FontHolder_t& fonts, Player& player,
	MusicPlayer& music, SoundPlayer& sounds,
	Actor::Type& p1Char, Actor::Type& p2Char,
	std::string& backGroundFilePath,
	std::string& platformfilePath,
	std::string& hudLeftFilePath,
	std::string& hudRightFilePath)

	:window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
	, music(&music)
	, sounds(&sounds)
	, p1Char(&p1Char)
	, p2Char(&p2Char)
	, backGroundFilePath(&backGroundFilePath)
	, platformfilePath(&platformfilePath)
	, hudLeftFilePath(&hudLeftFilePath)
	, hudRightFilePath(&hudRightFilePath)

{
}
