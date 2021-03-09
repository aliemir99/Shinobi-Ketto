#include "Actor.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "JsonFrameParser.h"
#include "Utility.h"
#include "DataTables.h"
#include "TextNode.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include "SoundPlayer.h"

/*
	Team:
	Date:
	Purpose:
*/
namespace
{
	const std::map<Actor::Type, ActorData> TABLE = initializeActorData();
}
Actor::Actor(Type type, const TextureHolder_t& textures, const FontHolder_t& fonts, Category::Type player)
	: Entity(100)
	, type_(type)
	, state_(State::Idle)
	, sprite_(textures.get(TABLE.at(type).texture))
	, direction_(Direction::Right)
	, travelDistance_(0.f)
	, directionIndex_(0)
	, worldBounderiesWidth(700.f)
	, countdown(0.f)
	, elapsedTime()
	, clock()
	, isJumping(false)
	, isFalling(false)
	, isGrounded(true)
	, canPlayDamageSound(true)
	, gravitySpeed(300)
	, groundHeight(95)
	, JumpDuration(.45)
	, category(player)

{
	for (auto a : TABLE.at(type).animations)
	{
		animations_[a.first] = a.second;
	}
	if (type_ == Actor::Type::Hero1) {
		sprite_.setTextureRect(sf::IntRect());

		sprite_.setScale(sf::Vector2f(1.5f, 1.5f));
		centerOrigin(sprite_);
	}
	if (type_ == Actor::Type::Hero2) {
		sprite_.setTextureRect(sf::IntRect());

		sprite_.setScale(sf::Vector2f(1.5f, 1.5f));
		centerOrigin(sprite_);
	}
	if (type_ == Actor::Type::Hero3) {
		sprite_.setTextureRect(sf::IntRect());
		sprite_.setScale(sf::Vector2f(1.5f, 1.5f));
		centerOrigin(sprite_);
	}
	if (type_ == Actor::Type::Platform) {
		//centerOrigin(sprite_);
		setState(Actor::State::Static);
		setDirection(Actor::Direction::Static);
	}

}
unsigned int Actor::getCategory() const
{
	return category;
}
void Actor::updateMovementPattern(sf::Time dt)
{
	// movement pattern
	if (Actor::Type::Hero1 == type_ || Actor::Type::Hero2 == type_ || Actor::Type::Hero3 == type_) {
		auto directions = TABLE.at(type_).directions;
		if (!directions.empty())
		{
			if (travelDistance_ > (directions[directionIndex_].distance))
			{
				directionIndex_ = (++directionIndex_) % directions.size();
				travelDistance_ = 0;
			}
			float radians = toRadian(directions[directionIndex_].angle + 90.f);
			float vx = getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);
			setVelocity(vx, vy);
			travelDistance_ += getMaxSpeed() * dt.asSeconds();
		}
		if (isJumping)
		{
			isGrounded = false;
			state_ = Actor::State::Jump;
			direction_ = Direction::Up;
			// Update how long the jump has been going
			TimeThisJump += dt.asSeconds();
			// Is the jump going upwards
			if (TimeThisJump < JumpDuration)
			{
				// Move up at twice gravity
				setPosition(getPosition().x, (getPosition().y) - (gravitySpeed * 2 * dt.asSeconds()));
			}
			else
			{
				isJumping = false;
				isFalling = true;
				state_ = Actor::State::Fall;
				direction_ = Direction::Down;
			}
		}
		// Apply gravity
		if (isFalling)
		{
			setPosition(getPosition().x, (getPosition().y) + (gravitySpeed * dt.asSeconds()));
			if (getPosition().y == groundHeight)
				isFalling = false;
			isJumping = false;
		}
		if (getPosition().y >= groundHeight) {
			isGrounded = true;
		}
	}

}
sf::FloatRect Actor::getBoundingRect() const
{
	auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());

	return box;
}
float Actor::getMaxSpeed() const
{
	return TABLE.at(type_).speed;
}
bool Actor::isMarkedForRemoval() const
{
	return false; // (state_ == State::Dead && animations_.at(state_).isFinished());
}

void Actor::setState(State state)
{
	state_ = state;
	if (Actor::Type::Hero1 == type_ || Actor::Type::Hero2 == type_ || Actor::Type::Hero3 == type_) {
		animations_.at({ state_ }).restart();
	}
}
Actor::State Actor::getState() const
{
	return state_;
}
Actor::Type Actor::getType() const
{
	return type_;
}
void Actor::playSound(EffectID effectType)
{
	soundplayer.play(effectType);

}

void Actor::setIsJumping(bool jump)
{
	isJumping = jump;
}
bool Actor::getIsJumping()
{
	return isJumping;
}
void Actor::setDirection(Actor::Direction direction)
{
	direction_ = direction;
}
Actor::Direction Actor::getDirection()
{
	return direction_;
}
bool Actor::isCurrentAnimationFinished()
{
	return animations_[state_].isFinished();
}
void Actor::updateStates()
{

	if (Actor::Type::Hero1 == type_ || Actor::Type::Hero2 == type_ || Actor::Type::Hero3 == type_) {
		//auto pair = std::make_pair(state_, direction_);


		if (isDestroyed())
			state_ = Actor::State::Dead;

		if (Actor::State::Dead == state_ && animations_[state_].isStarting()) {
			if (Actor::Type::Hero1 == type_)
				soundplayer.play(EffectID::H1GetHit);
			if (Actor::Type::Hero2 == type_)
				soundplayer.play(EffectID::H2GetHit);
			if (Actor::Type::Hero3 == type_)
				soundplayer.play(EffectID::H3GetHit);
		}
		if (Actor::State::Dead == state_ && animations_[state_].isFinished()) {
			//setState(Actor::State::Idle);
			//this->repair(100);
			//this->setPosition(350.f, 580.f);
			//animations_[state_].restart();
		}

		if (Actor::State::TakeHit == state_ && animations_[state_].isStarting()) {
			if (canPlayDamageSound) {
				playSound(EffectID::TakeDamage);
			}

			canPlayDamageSound = false;
		}

		if (Actor::State::TakeHit == state_ && animations_[state_].isFinished()) {
			canPlayDamageSound = true;
			setState(Actor::State::Idle);
		}

		if (Actor::State::Jump == state_ && animations_[state_].isFinished()) {


			setState(Actor::State::Fall);
		}
		if (Actor::State::Fall == state_ && animations_[state_].isFinished()) {
			if (this->getPosition().y >= 925) {
				setState(Actor::State::Idle);
				isFalling = false;
			}
		}

		if (Actor::State::Run == state_ && animations_[state_].isFinished()) {
			state_ = Actor::State::Idle;
		}
		if (Actor::State::Attack1 == state_ && animations_[state_].isStarting()) {
			if (Actor::Type::Hero1 == type_)
				soundplayer.play(EffectID::H1Attack1);
			if (Actor::Type::Hero2 == type_)
				soundplayer.play(EffectID::H2Attack1);
			if (Actor::Type::Hero3 == type_)
				soundplayer.play(EffectID::H3Attack1);
		}

		if (Actor::State::Attack1 == state_ && animations_[state_].isFinished()) {

			setState(Actor::State::Attack2);

		}
		if (Actor::State::Attack2 == state_ && animations_[state_].isStarting()) {
			if (Actor::Type::Hero1 == type_)
				soundplayer.play(EffectID::H1Attack2);
			if (Actor::Type::Hero2 == type_)
				soundplayer.play(EffectID::H2Attack2);
			if (Actor::Type::Hero3 == type_)
				soundplayer.play(EffectID::H3Attack2);

		}
		if (Actor::State::Attack2 == state_ && animations_[state_].isFinished()) {

			setState(Actor::State::Idle);
		}
	}
	//std::cout << (int)getState() << " " << (int)getDirection() << std::endl;
}


void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	updateStates();
	updateSounds();
	if (Actor::Type::Hero1 == type_ || Actor::Type::Hero2 == type_ || Actor::Type::Hero3 == type_) {
		if (state_ != Actor::State::Dead) {
			//auto pair = std::make_pair(state_, direction_);
			auto rec = animations_.at(state_).update(dt);
			sprite_.setTextureRect(rec);
		}

		if (state_ == State::Dead)
		{
			//auto pair = std::make_pair(state_, direction_);
			auto rec = animations_.at(state_).update(dt);

			auto x = sprite_.getPosition().x;
			auto y = sprite_.getPosition().y;
			sprite_.setTextureRect(rec);
		}

		centerOrigin(sprite_);
		if (state_ != State::Dead) // dont move it while dying
			Entity::updateCurrent(dt, commands);
	}

	updateMovementPattern(dt);
}
void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
void Actor::updateSounds()
{
	soundplayer.setListenerPosition(sprite_.getPosition());
	soundplayer.removeStoppedSounds();
}

