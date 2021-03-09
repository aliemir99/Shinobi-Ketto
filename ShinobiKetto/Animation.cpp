#include "Animation.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
Animation::Animation()
	: sprite()
	, frameSize()
	, numFrames(0)
	, currentFrame(0)
	, duration(sf::Time::Zero)
	, elapsedTime(sf::Time::Zero)
	, repeat(false)
{
}

Animation::Animation(const sf::Texture& texture)
	: sprite(texture)
	, frameSize()
	, numFrames(0)
	, currentFrame(0)
	, duration(sf::Time::Zero)
	, elapsedTime(sf::Time::Zero)
	, repeat(false)
{
}

void Animation::setTexture(const sf::Texture& texture)
{
	sprite.setTexture(texture);
}

const sf::Texture* Animation::getTexture() const
{
	return sprite.getTexture();
}

void Animation::setFrameSize(sf::Vector2i fs)
{
	frameSize = fs;
}

sf::Vector2i Animation::getFrameSize() const
{
	return frameSize;
}

void Animation::setNumFrames(std::size_t nf)
{
	numFrames = nf;
}

std::size_t Animation::getNumFrames() const
{
	return numFrames;
}

void Animation::setDuration(sf::Time d)
{
	duration = d;
}

sf::Time Animation::getDuration() const
{
	return duration;
}

void Animation::setRepeating(bool flag)
{
	repeat = flag;
}

bool Animation::isRepeating() const
{
	return repeat;
}

void Animation::restart()
{
	currentFrame = 0;
}

bool Animation::isFinished() const
{
	return currentFrame >= numFrames;
}

sf::FloatRect Animation::getLocalBounds() const
{
	return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f>(getFrameSize()));
}

sf::FloatRect Animation::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

void Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = duration / static_cast<float>(numFrames);
	elapsedTime += dt;

	sf::Vector2i textureBounds(sprite.getTexture()->getSize());
	sf::IntRect textureRect = sprite.getTextureRect();

	if (currentFrame == 0)
		textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);

	while (elapsedTime >= timePerFrame && (currentFrame <= numFrames || repeat))
	{
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			//shift down a row
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		elapsedTime -= timePerFrame;
		if (repeat)
		{
			currentFrame = (currentFrame + 1) % numFrames;

			if (currentFrame == 0)
				textureRect = sf::IntRect(0, 0, frameSize.x, frameSize.y);
		}
		else
		{
			currentFrame += 1;
		}

	}
	sprite.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}
