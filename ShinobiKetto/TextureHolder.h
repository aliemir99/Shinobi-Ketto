#pragma once
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include <string>

enum class TextureID { Landscape, Airplane, Missile };

class TextureHolder
{
public:
	void					load(TextureID id, const std::string& filename);

	const sf::Texture& get(TextureID id)const;


private:
	std::map <TextureID, std::unique_ptr<sf::Texture>> textureMap;
};


