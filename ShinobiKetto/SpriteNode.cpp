#include "SpriteNode.h"
SpriteNode::SpriteNode(const sf::Texture& texture) : sprite(texture)
{
}
SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) : sprite(texture, textureRect)
{
}

sf::Sprite SpriteNode::getSprite()
{
	return sprite;
}


void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
