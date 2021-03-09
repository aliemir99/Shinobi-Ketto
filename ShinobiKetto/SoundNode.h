#pragma once
#include "ResourceIdentifier.h"
#include "SceneNode.h"
#include "SoundPlayer.h"
class SoundNode : public SceneNode
{
public:
	SoundNode(SoundPlayer& player);
	void						playSound(EffectID effect, sf::Vector2f position);

	virtual unsigned int		getCategory() const override;

private:
	SoundPlayer& sounds;

};


