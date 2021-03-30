#include "GameState.h"
#include "MusicPlayer.h"
#include <SFML/Graphics/RenderWindow.hpp>
GameState::GameState(StateStack& stack, Context context)
	:State(stack, context)
	, world(*context.window, *context.fonts, *context.sounds,
		*context.p1Char, *context.p2Char, *context.backGroundFilePath
		, *context.platformfilePath, *context.hudLeftFilePath, *context.hudRightFilePath)
	, player(*context.player)
{

	using musicTypes = MusicPlayer::MUSIC_TYPE;
	switch (context.music->getType())
	{
	case musicTypes::FOREST:
		context.music->play(MusicID::ForestTheme);
		break;
	case musicTypes::JUNGLE:
		context.music->play(MusicID::JungleTheme);
		break;
	case musicTypes::LAKE:
		context.music->play(MusicID::LakeTheme);
		break;
	case musicTypes::COUNTY:
		context.music->play(MusicID::CountyTheme);
		break;
	default:
		break;
	}

	context.sounds->play(EffectID::GongHit);
}

void GameState::draw()
{
	auto& window = *getContext().window;
	world.draw();

}

bool GameState::update(sf::Time dt)
{
	world.update(dt);
	if (world.isRoundOver) {
		if (world.p1Rounds < 3 && world.p2Rounds < 3) {
			requestStackPush(StateID::RoundOver);
			world.isRoundOver = false;
			world.resetRound();
		}

	}
	if (world.p1Rounds >= 3) {
		SoundPlayer& sound = *getContext().sounds;
		sound.play(EffectID::GongRoll);
		player.setMissionStatus(Player::MissionStatus::SuccessP1);
		requestStackPush(StateID::GameOver);
	}
	else if (world.p2Rounds >= 3) {
		SoundPlayer& sound = *getContext().sounds;
		sound.play(EffectID::GongRoll);
		player.setMissionStatus(Player::MissionStatus::SuccessP2);
		requestStackPush(StateID::GameOver);
	}
	CommandQueue& commands = world.getCommands();
	player.handleRealTimeInput(commands);
	return true;
}

bool GameState::handleEvents(const sf::Event& event)
{
	CommandQueue& commands = world.getCommands();
	player.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(StateID::Pause);
	//Q pressed, trigger the menu state
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		requestStackPush(StateID::Menu);

	return false;
}
