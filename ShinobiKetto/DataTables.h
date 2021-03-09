#pragma once

#include "ResourceIdentifier.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <map>
#include <vector>
#include <functional>
#include "Actor.h"

struct Direction {
	Direction(float angle, float distance)
		: angle(angle)
		, distance(distance)
	{}
	float angle;
	float distance;
};

struct ActorData
{
	int									hitpoints;
	int									damageDone;
	float								speed;
	TextureID							texture;
	std::map<Actor::State, Animation2>	animations;
	std::vector<Direction>				directions;
};

//functions to fill data tables


std::map<Actor::Type, ActorData>			initializeActorData();