#include "TextNode.h"
#include "Utility.h"
#include <SFML/Graphics/RenderWindow.hpp>
TextNode::TextNode(const FontHolder_t& fonts, const std::string& text_)
{

	text.setFont(fonts.get(FontID::Main));
	text.setCharacterSize(20);
	setString(text_);
}

void TextNode::setString(const std::string& text_)
{
	text.setString(text_);
	centerOrigin(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}
