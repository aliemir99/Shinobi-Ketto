#include "Player.h"
#include <algorithm>
#include "CommandQueue.h"
#include "Actor.h"
#include <iostream>
#include "State.h"

/*
	Team: std::pair(Ali-Ibrahim)
	Date: 2020-12-07
	Purpose: Create a frogger replica using GEX Engine
*/


Player::Player()
	: currentMissionStatus(MissionStatus::Running)
	, sounds()
	, p2Timer(sf::Clock())

{
	initializeKeyBindings();
	initializeActions();
}

void Player::initializeKeyBindings()
{
	keyBindings[sf::Keyboard::A] = Action::P1MoveLeft;
	keyBindings[sf::Keyboard::D] = Action::P1MoveRight;
	keyBindings[sf::Keyboard::W] = Action::P1MoveUp;
	keyBindings[sf::Keyboard::S] = Action::P1MoveDown;
	keyBindings[sf::Keyboard::C] = Action::P1Attack;

	keyBindings2[sf::Keyboard::Left] = Action::P2MoveLeft;
	keyBindings2[sf::Keyboard::Right] = Action::P2MoveRight;
	keyBindings2[sf::Keyboard::Up] = Action::P2MoveUp;
	keyBindings2[sf::Keyboard::Down] = Action::P2MoveDown;
	keyBindings2[sf::Keyboard::M] = Action::P2Attack;

}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = keyBindings.find(event.key.code);
		if (found != keyBindings.end())
			commands.push(actionBindings[found->second]);

		auto found2 = keyBindings2.find(event.key.code);
		if (found2 != keyBindings2.end())
			commands.push(actionBindings2[found2->second]);
	}
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (auto pair : keyBindings) {
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
			commands.push(actionBindings[pair.second]);
		}
	}
	for (auto pair : keyBindings2) {
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
			commands.push(actionBindings2[pair.second]);
		}
	}

}


void Player::setMissionStatus(MissionStatus status)
{
	currentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
	return currentMissionStatus;
}


void Player::initializeActions()
{
	const float playerSpeed = 5.f;
	const float jumpSpeed = 1500.f;


	actionBindings[Action::P1MoveLeft].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			if (a.getDirection() != Actor::Direction::Left) {
				a.setScale(-1 * a.getScale().x, a.getScale().y);
				a.setDirection(Actor::Direction::Left);
			}
			if (a.getState() != Actor::State::Run && a.getPosition().y > 850)
				a.setState(Actor::State::Run);
			else {

			}
			a.setVelocity(sf::Vector2f(-playerSpeed, 0.f));
			a.move(sf::Vector2f(-playerSpeed, 0.f));


		});
	actionBindings[Action::P1MoveRight].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			if (a.getDirection() != Actor::Direction::Right) {
				a.setScale(-1 * a.getScale().x, a.getScale().y);
				a.setDirection(Actor::Direction::Right);
			}
			if (a.getState() != Actor::State::Run && a.getPosition().y > 850)
				a.setState(Actor::State::Run);
			else {

			}


			a.setVelocity(sf::Vector2f(10.f, 0.f));
			a.move(sf::Vector2f(playerSpeed, 0.f));

		});

	actionBindings[Action::P1MoveUp].action = derivedAction<Actor>(
		[jumpSpeed](Actor& a, sf::Time dt) {
			auto playerPosfromTop = a.getBoundingRect().height
				+ a.getPosition().y;
			if (a.getPosition().y > 850) {


				if (playerPosfromTop > 650.f) {
					if (!a.isJumping && !a.isFalling)
					{
						a.isJumping = true;
						a.TimeThisJump = 0;
						a.JustJumped = true;
					}
					a.setState(Actor::State::Jump);
					a.accelerate(0.f, -jumpSpeed * 15);




					a.isJumping = false;
					a.isFalling = true;

				}
			}
			std::cout << playerPosfromTop << std::endl;



			//std::cout << (int)a.getState() << " " << (int)a.getDirection() << std::endl;

		});
	actionBindings[Action::P1MoveDown].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			//the falling is going to be managed when jump animation is finished
			a.setState(Actor::State::Fall);
			a.accelerate(sf::Vector2f(0.f, playerSpeed));
		});
	actionBindings[Action::P1Attack].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			if (a.getState() == Actor::State::Attack2 && a.isCurrentAnimationFinished()) {
				a.setState(Actor::State::Idle);
			}
			if (a.getState() == Actor::State::Attack1 && a.isCurrentAnimationFinished()) {
				a.setState(Actor::State::Attack2);
			}

			if (a.getState() == Actor::State::Idle || a.getState() == Actor::State::Run) {
				a.setState(Actor::State::Attack1);
			}
			//a.accelerate(sf::Vector2f(playerSpeed, -0.f));
		});

	actionBindings2[Action::P2MoveLeft].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			if (a.getDirection() != Actor::Direction::Left) {
				a.setScale(-1 * a.getScale().x, a.getScale().y);
				a.setDirection(Actor::Direction::Left);
			}
			if (a.getState() != Actor::State::Run && a.getPosition().y > 850)
				a.setState(Actor::State::Run);

			a.setVelocity(sf::Vector2f(-playerSpeed, 0.f));
			a.move(sf::Vector2f(-playerSpeed, 0.f));


		});
	actionBindings2[Action::P2MoveRight].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {


			if (a.getDirection() != Actor::Direction::Right) {
				a.setScale(-1 * a.getScale().x, a.getScale().y);
				a.setDirection(Actor::Direction::Right);
			}
			if (a.getState() != Actor::State::Run && a.getPosition().y > 850)
				a.setState(Actor::State::Run);


			a.setVelocity(sf::Vector2f(10.f, 0.f));
			a.move(sf::Vector2f(playerSpeed, 0.f));

		});
	//make this an event
	actionBindings2[Action::P2MoveUp].action = derivedAction<Actor>(
		[=](Actor& a, sf::Time dt) {
			auto playerPosfromTop = a.getBoundingRect().height
				+ a.getPosition().y;
			if (a.getPosition().y > 850) {


				if (playerPosfromTop > 650.f) {
					if (!a.isJumping && !a.isFalling)
					{
						a.isJumping = true;
						a.TimeThisJump = 0;
						a.JustJumped = true;
					}
					a.setState(Actor::State::Jump);
					a.accelerate(0.f, -jumpSpeed * 15);




					a.isJumping = false;
					a.isFalling = true;

				}
			}
		});
	actionBindings2[Action::P2MoveDown].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			//the falling is going to be managed when jump animation is finished
			a.setState(Actor::State::Fall);
			a.accelerate(sf::Vector2f(0.f, playerSpeed));
		});
	actionBindings2[Action::P2Attack].action = derivedAction<Actor>(
		[playerSpeed](Actor& a, sf::Time dt) {
			if (a.getState() == Actor::State::Attack2 && a.isCurrentAnimationFinished()) {
				a.setState(Actor::State::Idle);

			}
			if (a.getState() == Actor::State::Attack1 && a.isCurrentAnimationFinished()) {
				a.setState(Actor::State::Attack2);
			}

			if (a.getState() == Actor::State::Idle || a.getState() == Actor::State::Run) {
				a.setState(Actor::State::Attack1);
			}
			//a.accelerate(sf::Vector2f(playerSpeed, -0.f));
		});


	for (auto& pair : actionBindings) {

		pair.second.category = Category::Player1;
		//if (Actor::Type::Hero1 == actor1)
		//	pair.second.category = Category::Hero1;
		//if (Actor::Type::Hero2 == actor1)
		//	pair.second.category = Category::Hero2;
		//if (Actor::Type::Hero3 == actor1)
		//	pair.second.category = Category::Hero3;
	}
	for (auto& pair : actionBindings2) {
		pair.second.category = Category::Player2;
		//if (Actor::Type::Hero1 == actor1)
		//	pair.second.category = Category::Hero1;
		//if (Actor::Type::Hero2 == actor1)
		//	pair.second.category = Category::Hero2;
		//if (Actor::Type::Hero3 == actor1)
		//	pair.second.category = Category::Hero3;
	}


}
bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
	case Action::P1MoveLeft:
	case Action::P2MoveLeft:
	case Action::P1MoveRight:
	case Action::P2MoveRight:
	case Action::P1MoveDown:
	case Action::P2MoveDown:
	case Action::P1Attack:
	case Action::P2Attack:
		return true;
		break;
	case Action::P1MoveUp:
	case Action::P2MoveUp:
	default:
		return false;
		break;
	}
}

