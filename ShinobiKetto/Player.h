#pragma once

#include <SFML/Window/Event.hpp>
#include"Command.h"
#include <map>
#include "SoundPlayer.h"
#include "Actor.h"
/*
	Team: std::pair(Ali-Ibrahim)
	Date: 2020-12-07
	Purpose: Create a frogger replica using GEX Engine
*/

//forward decleration
class CommandQueue;

class Player
{
public:
	enum class Action
	{
		P1MoveLeft,
		P2MoveLeft,
		P1MoveRight,
		P2MoveRight,
		P1MoveUp,
		P2MoveUp,
		P1MoveDown,
		P2MoveDown,
		P1Attack,
		P2Attack,

		ActionCount
	};
	enum class MissionStatus
	{
		Running,
		SuccessP1,
		SuccessP2,
		Failure,
	};

public:
	Player();
	void									initializeKeyBindings();
	void									handleEvent(const sf::Event& event, CommandQueue& commands);
	void									handleRealTimeInput(CommandQueue& commands);

	void									setMissionStatus(MissionStatus status);
	MissionStatus							getMissionStatus() const;

private:
	void									initializeActions();
	static bool								isRealTimeAction(Action action);

	MissionStatus							currentMissionStatus;
	SoundPlayer								sounds;
private:
	std::map<sf::Keyboard::Key, Action>		keyBindings;
	std::map<sf::Keyboard::Key, Action>		keyBindings2;
	std::map<Action, Command>				actionBindings;
	std::map<Action, Command>				actionBindings2;



	sf::Clock								p2Timer;


};

