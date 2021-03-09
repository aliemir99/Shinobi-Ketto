#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Actor.h"
#include "CommandQueue.h"
#include "Command.h"
#include "SoundPlayer.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <SFML/Graphics/CircleShape.hpp>

/*
	Team: std::pair(Ali-Ibrahim)
	Date: 2020-12-07
	Purpose: Create a frogger replica using GEX Engine
*/

// Forward declaration
namespace sf
{
	class RenderWindow;
	class RenderTarget;
}
class World : private sf::NonCopyable
{
public:
	explicit							World(sf::RenderTarget& outputTarget, FontHolder_t& fonts, SoundPlayer& sounds
		, Actor::Type p1Char, Actor::Type p2Char, std::string backGroundFilePath
		, std::string platformFilePath, std::string hudLeftFilePath, std::string hudRightFilePath);
	void								update(sf::Time dt);
	void								draw();

	CommandQueue& getCommands();
	bool								isRoundOver;
	int									p1Rounds;
	int									p2Rounds;
	void								resetRound();
private:
	void								loadTextures();
	void								buildScene();

	void								addEnemies();
	void								addEnemy(Actor::Type type, float relX, float relY);

	void								spawnEnemies();

	void								adaptPlayerVelocity();
	void								adaptPlayerPosition();

	void								updateSounds();
	void								dealDamage(std::string toWhom);
	sf::FloatRect						getViewBounds() const;

	void								handleCollisions();
	bool								matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

	void								setPlayerHudScoreText(size_t score);
	void								resetHealthBars();
private:
	enum Layer
	{
		Background,
		LowerAir,
		UpperAir,
		LayerCount
	};

	struct SpawnPoint {
		SpawnPoint(Actor::Type type, float x, float y)
			:type(type), x(x), y(y) {}
		Actor::Type type;
		float x, y;
	};

private:
	sf::RenderTarget& target;
	sf::RenderTexture					sceneTexture;
	sf::View							worldView;
	TextureHolder_t						textures;
	const FontHolder_t& fonts;
	SoundPlayer& sounds;
	Actor::Type& p1Char;
	Actor::Type& p2Char;
	std::string& backGroundFilePath;
	std::string& platformFilePath;
	std::string& hudLeftFilePath;
	std::string& hudRightFilePath;

	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;
	CommandQueue						commandQueue;

	sf::FloatRect						worldBounds;
	sf::Vector2f						spawnPosition;
	sf::Vector2f						p1StartingPos;
	sf::Vector2f						p2StartingPos;

	Actor* playerActor;
	Actor* player2Actor;
	Actor* platformActor;
	std::vector<SpawnPoint>				enemySpawnPoints;
	std::vector<Actor*>					activeEnemies;
	std::vector<sf::Sprite>				playerLives;


	sf::Text							playerScoreHud;
	sf::Text							timerText;

	sf::RectangleShape					leftHealthBar;
	sf::RectangleShape					rightHealthBar;

	sf::CircleShape						leftLight1;
	sf::CircleShape						leftLight2;
	sf::CircleShape						leftLight3;

	sf::CircleShape						rightLight1;
	sf::CircleShape						rightLight2;
	sf::CircleShape						rightLight3;


};


