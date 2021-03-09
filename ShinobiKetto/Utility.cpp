#include "Utility.h"
#include "Animation.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <random>

namespace {
	const float PI = 3.1415927;

	std::mt19937 createRandomEngine()
	{
		std::random_device r;
		return std::mt19937(r());
	}
	auto RandomEngine = createRandomEngine();
}


void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}
void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(Animation& animation)
{
	sf::FloatRect bounds = animation.getLocalBounds();
	animation.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

float toDegree(float radian)
{
	return (radian * 180) / PI;
}

float toRadian(float degree)
{
	return (degree * PI) / 180;
}

float length(sf::Vector2f v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(sf::Vector2f v)
{
	if (length(v) > 0)
		return (v / length(v));
	else
		return v;
}

int randomInt(int exclusiveMax)
{
	std::uniform_int_distribution<> distribution(0, exclusiveMax - 1);
	return distribution(RandomEngine);
}

sf::IntRect flip(const sf::IntRect& rec)
{
	auto tmp = rec;
	tmp.left += tmp.width;
	tmp.width *= -1;
	return tmp;
}
