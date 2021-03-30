#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
class SpriteNode : public SceneNode
{
public:


	explicit					SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
	sf::Sprite					getSprite();
private:
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
	sf::Sprite		sprite;

};