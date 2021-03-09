#include "TextureHolder.h"
#include <stdexcept>
#include <cassert>

void TextureHolder::load(TextureID id, const std::string& filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	if (!texture->loadFromFile(filename))
	{
		throw std::runtime_error("TextureHolder::Load - failed to load" + filename);
	}

	auto rc = textureMap.insert(std::make_pair(id, std::move(texture)));
	assert(rc.second);
}

const sf::Texture& TextureHolder::get(TextureID id) const
{
	auto found = textureMap.find(id);
	assert(found != textureMap.end());

	return *found->second;
}
