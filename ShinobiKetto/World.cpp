#include "World.h"
#include <limits>
#include <algorithm>
#include "DataTables.h"
#include "SoundNode.h"
#include <iostream>

/*
	Team:
	Date:
	Purpose:
*/
World::World(sf::RenderTarget& outputTarget, FontHolder_t& fonts, SoundPlayer& sounds
	, Actor::Type p1Char, Actor::Type p2Char, std::string backGroundFilePath
	, std::string platformFilePath, std::string hudLeftFilePath, std::string hudRightFilePath)
	: target(outputTarget)
	, sceneTexture()
	, worldView(target.getDefaultView())
	, textures()
	, fonts(fonts)
	, sounds(sounds)
	, p1Char(p1Char)
	, p2Char(p2Char)
	, backGroundFilePath(backGroundFilePath)
	, platformFilePath(platformFilePath)
	, hudLeftFilePath(hudLeftFilePath)
	, hudRightFilePath(hudRightFilePath)
	, sceneGraph()
	, sceneLayers()
	, commandQueue()
	, worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y) //length of background scroller
	, spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2)
	, playerActor(nullptr)
	, player2Actor(nullptr)
	, platformActor(nullptr)
	, leftHealthBar(sf::Vector2f(400.f, 43.f))
	, rightHealthBar(sf::Vector2f(400.f, 43.f))
	, leftLight1(10.f)
	, leftLight2(10.f)
	, leftLight3(10.f)
	, rightLight1(10.f)
	, rightLight2(10.f)
	, rightLight3(10.f)
	, isRoundOver(false)
	, p1StartingPos(worldView.getSize().x / 2.f - worldView.getSize().x / 4.f, 1000)
	, p2StartingPos(worldView.getSize().x / 2.f + worldView.getSize().x / 4.f, 1000)
	, p1Rounds(0)
	, p2Rounds(0)
	, roundTimer(90)

{
	sceneTexture.create(target.getSize().x, target.getSize().y);
	loadTextures();
	buildScene();
	worldView.setCenter(spawnPosition);

	roundHud.setFont(fonts.get(FontID::Main));
	roundHud.setString("Round 1");
	roundHud.setScale(2.f, 2.f);
	roundHud.setPosition((worldView.getSize().x / 2.f) - 125, 35);
	roundHud.setFillColor(sf::Color::Red);

	timerText.setFont(fonts.get(FontID::Main));
	timerText.setString("Timer");
	timerText.setScale(2.f, 2.f);
	timerText.setPosition((worldView.getSize().x / 2.f) - 50, 130.f);
	timerText.setFillColor(sf::Color::Yellow);

	leftHealthBar.setFillColor(sf::Color::Green);
	leftHealthBar.setPosition(235.f, 140.f);

	rightHealthBar.setFillColor(sf::Color::Green);
	rightHealthBar.setPosition(1675.f, 183.f);
	rightHealthBar.setRotation(180.f);

	leftLight1.setFillColor(sf::Color::Red);
	leftLight1.setPosition(293.f, 220.f);

	leftLight2.setFillColor(sf::Color::Yellow);
	leftLight2.setPosition(365.f, 220.f);

	leftLight3.setFillColor(sf::Color::Magenta);
	leftLight3.setPosition(437.f, 220.f);


	rightLight3.setFillColor(sf::Color::Magenta);
	rightLight3.setPosition(1453, 220.f);

	rightLight2.setFillColor(sf::Color::Yellow);
	rightLight2.setPosition(1525.f, 220.f);

	rightLight1.setFillColor(sf::Color::Red);
	rightLight1.setPosition(1596.f, 220.f);
}


void World::update(sf::Time dt)
{
	//reset player velocity
	playerActor->setVelocity(0.f, 0.f);
	player2Actor->setVelocity(0.f, 0.f);
	platformActor->setVelocity(0.f, 0.f);

	
	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt);
	}
	adaptPlayerVelocity();

	//Collision detection and response(may destroy entities)
	handleCollisions();

	
	sceneGraph.update(dt, getCommands());
	adaptPlayerPosition();
	if (playerActor->isBlocking) {
		playerActor->shieldTimer -= .1;
		
	}
	if (playerActor->shieldTimer <= 0) {
		playerActor->deactivateShield();
	}
	if (player2Actor->isBlocking ) {
		player2Actor->shieldTimer -= .1;
		
	}
	if (player2Actor->shieldTimer <= 0) {
		player2Actor->deactivateShield();
	}


	updateSounds();
	if (playerActor->getState() == Actor::State::Dead && playerActor->isCurrentAnimationFinished()) {
		isRoundOver = true;
		p2Rounds++;
	}
	if (player2Actor->getState() == Actor::State::Dead && player2Actor->isCurrentAnimationFinished()) {
		isRoundOver = true;
		p1Rounds++;
	}
	setRoundText(p1Rounds + p2Rounds + 1);

	if (roundTimer > 0) {
		setTimerText(roundTimer);
		roundTimer -= .02;
	}
	else {
		isRoundOver = true;
		if (leftHealthBar.getGlobalBounds().width > rightHealthBar.getGlobalBounds().width) {
			p1Rounds++;
		}
		else {
			p2Rounds++;
		}
	}

}

void World::draw()
{
	target.setView(worldView);
	target.draw(sceneGraph);

	target.draw(leftHealthBar);
	target.draw(rightHealthBar);
	target.draw(roundHud);
	target.draw(timerText);

	if(playerActor->isBlocking)
		target.draw(playerActor->shield);
	
	if (player2Actor->isBlocking)
		target.draw(player2Actor->shield);
	
	//DRAW ONLY WHEN FIRST PLAYER WINS A ROUND
	if (p1Rounds >= 3) {
		target.draw(leftLight1);
		target.draw(leftLight2);
		target.draw(leftLight3);
	}
	else if (p1Rounds == 2) {
		target.draw(leftLight1);
		target.draw(leftLight2);
	}
	else if (p1Rounds == 1) {
		target.draw(leftLight1);
	}

	//DRAW ONLY WHEN SECOND PLAYER OR AI WINS A ROUND
	if (p2Rounds >= 3) {
		target.draw(rightLight1);
		target.draw(rightLight2);
		target.draw(rightLight3);
	}
	else if (p2Rounds == 2) {
		target.draw(rightLight1);
		target.draw(rightLight2);
	}
	else if (p2Rounds == 1) {
		target.draw(rightLight1);
	}


}

CommandQueue& World::getCommands()
{
	return commandQueue;
}

void World::loadTextures()
{
	textures.load(TextureID::Background, backGroundFilePath);
	textures.load(TextureID::platform, platformFilePath);
	textures.load(TextureID::Hero1, "Media/Textures/Fight/hero1.png");
	textures.load(TextureID::Hero2, "Media/Textures/Fight/hero2.png");
	textures.load(TextureID::Hero3, "Media/Textures/Fight/hero3.png");
	textures.load(TextureID::LeftHUD, hudLeftFilePath);
	textures.load(TextureID::RightHUD, hudRightFilePath);

}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i) {

		Category::Type category =
			(i == LowerAir) ? Category::Type::SceneAirLayer : Category::Type::None;

		SceneNode::Ptr layer(new SceneNode(category));
		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

	//add sound effect node
	std::unique_ptr<SoundNode> soundNode(new SoundNode(sounds));
	sceneGraph.attachChild(std::move(soundNode));

	//prepare background texture
	sf::Texture& texture = textures.get(TextureID::Background);

	float viewHeight = worldView.getSize().y;
	sf::IntRect textureRect(worldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	std::unique_ptr<SpriteNode> map(new SpriteNode(texture, textureRect));
	map->setPosition(0, 0);
	sceneLayers[Background]->attachChild(std::move(map));

	sf::Texture& leftHudTexture = textures.get(TextureID::LeftHUD);
	std::unique_ptr<SpriteNode> leftHud(new SpriteNode(leftHudTexture));
	leftHud->setPosition(50, 100);
	leftHud->setScale(1.5f, 1.5f);
	sceneLayers[Background]->attachChild(std::move(leftHud));

	sf::Texture& rightHudTexture = textures.get(TextureID::RightHUD);
	std::unique_ptr<SpriteNode> rightHud(new SpriteNode(rightHudTexture));
	rightHud->setPosition(1260, 100);
	rightHud->setScale(1.5f, 1.5f);
	sceneLayers[Background]->attachChild(std::move(rightHud));

	std::unique_ptr<Actor> platform(new Actor(Actor::Type::Platform, textures, fonts, Category::Platform));
	platformActor = platform.get();
	platformActor->setPosition(0, 955);
	platformActor->setScale(1.2f, 1.2f);
	sceneLayers[Background]->attachChild(std::move(platform));

	//add player character
	std::unique_ptr<Actor> leader(new Actor(p1Char, textures, fonts, Category::Player1));
	leader->setScale(2.2f, 2.2f);
	playerActor = leader.get();
	playerActor->setPosition(p1StartingPos);
	playerActor->setVelocity(80.f, 0.f);
	sceneLayers[UpperAir]->attachChild(std::move(leader));

	std::unique_ptr<Actor> player2(new Actor(p2Char, textures, fonts, Category::Player2));
	player2->setScale(2.2f, 2.2f);
	player2Actor = player2.get();
	player2Actor->setPosition(p2StartingPos);
	player2Actor->setVelocity(80.f, 0.f);
	sceneLayers[UpperAir]->attachChild(std::move(player2));
	//addEnemies();


}

void World::addEnemies()
{

}

void World::addEnemy(Actor::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, relX, relY);
	enemySpawnPoints.push_back(spawn);

}

void World::spawnEnemies()
{
	while (!enemySpawnPoints.empty())
	{
		auto& spawn = enemySpawnPoints.back();

		std::unique_ptr<Actor> enemy(new Actor(spawn.type, textures, fonts, Category::Platform));
		enemy->setPosition(spawn.x, spawn.y);
		sceneLayers[LowerAir]->attachChild(std::move(enemy));
		sceneLayers[UpperAir]->attachChild(std::move(enemy));

		// Enemy is spawned, remove from the list to spawn
		enemySpawnPoints.pop_back();
	}
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = playerActor->getVelocity();
	// If moving diagonally, normalize the velocity
	if (velocity.x != 0.f && velocity.y != 0.f)
		playerActor->setVelocity(velocity / std::sqrt(2.f));

	sf::Vector2f velocity2 = player2Actor->getVelocity();
	// If moving diagonally, normalize the velocity
	if (velocity2.x != 0.f && velocity2.y != 0.f)
		player2Actor->setVelocity(velocity2 / std::sqrt(2.f));

}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;
	const float hudDistance = 70.f;
	sf::Vector2f position = playerActor->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance + 100);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance - 100);
	position.y = std::max(position.y, viewBounds.top + 120);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - (borderDistance + hudDistance + 100));
	playerActor->setPosition(position);

	sf::Vector2f position2 = player2Actor->getPosition();
	position2.x = std::max(position2.x, viewBounds.left + borderDistance + 100);
	position2.x = std::min(position2.x, viewBounds.left + viewBounds.width - borderDistance - 100);
	position2.y = std::max(position2.y, viewBounds.top + 120);
	position2.y = std::min(position2.y, viewBounds.top + viewBounds.height - (borderDistance + hudDistance + 100));
	player2Actor->setPosition(position2);
}



void World::updateSounds()
{
	sounds.setListenerPosition(playerActor->getWorldPosition());
	sounds.removeStoppedSounds();
}



void World::dealDamage(std::string toWhom)
{	//p1 takes damage
	if (toWhom == "p1") {
		if (player2Actor->getState() == Actor::State::Attack1) {

			if (leftHealthBar.getSize().x >= 0) {
				leftHealthBar.setSize(sf::Vector2f(leftHealthBar.getSize().x - 3, leftHealthBar.getSize().y));
			}
			else {
				playerActor->setState(Actor::State::Dead);
			}
		}
		if (player2Actor->getState() == Actor::State::Attack2) {
			if (leftHealthBar.getSize().x >= 0) {
				leftHealthBar.setSize(sf::Vector2f(leftHealthBar.getSize().x - 6, leftHealthBar.getSize().y));
			}
			else {
				playerActor->setState(Actor::State::Dead);
			}
		}
	}
	//p2 takes damage
	if (toWhom == "p2") {

		if (playerActor->getState() == Actor::State::Attack1) {
			if (rightHealthBar.getSize().x >= 0) {
				rightHealthBar.setSize(sf::Vector2f(rightHealthBar.getSize().x - 3, rightHealthBar.getSize().y));
			}
			else {
				player2Actor->setState(Actor::State::Dead);
			}
		}

		if (playerActor->getState() == Actor::State::Attack2) {

			if (rightHealthBar.getSize().x >= 0) {
				rightHealthBar.setSize(sf::Vector2f(rightHealthBar.getSize().x - 6, rightHealthBar.getSize().y));
			}
			else {
				player2Actor->setState(Actor::State::Dead);
			}
		}
	}

}




sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());
}


bool World::matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::setRoundText(size_t score)
{
	roundHud.setString("Round " + std::to_string(score));

}
void World::setTimerText(float time)
{

	timerText.setString(std::to_string((int)time));

}


void World::resetHealthBars()
{
	leftHealthBar.setSize(sf::Vector2f(400.f, 43.f));
	rightHealthBar.setSize(sf::Vector2f(400.f, 43.f));
}

void World::resetRound()
{
	playerActor->setPosition(p1StartingPos);
	player2Actor->setPosition(p2StartingPos);
	resetHealthBars();
	roundTimer = 90;
	playerActor->setState(Actor::State::Idle);
	player2Actor->setState(Actor::State::Idle);
	isRoundOver = false;
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);

	for (SceneNode::Pair pair : collisionPairs)
	{
		//PLAYER 1 COLLISION WITH PLATFORM
		if (matchesCategories(pair, Category::Player1, Category::Platform))
		{
			if (playerActor->getBoundingRect().intersects(platformActor->getBoundingRect()))
			{
				if (playerActor->getState() == Actor::State::Fall) {
					playerActor->setState(Actor::State::Idle);
				}
			}
		}
		//PLAYER 2 COLLISION WITH PLATFORM
		if (matchesCategories(pair, Category::Player2, Category::Platform))
		{
			if (player2Actor->getBoundingRect().intersects(platformActor->getBoundingRect()))
			{
				if (player2Actor->getState() == Actor::State::Fall) {
					player2Actor->setState(Actor::State::Idle);
				}
			}

		}

		//PLAYERS COLLIDING
		if (matchesCategories(pair, Category::Player1, Category::Player2))
		{
			if (playerActor->getBoundingRect().intersects(player2Actor->getBoundingRect()))
			{
				//P1 runs into player 2
				if (playerActor->getDirection() == Actor::Direction::Right && playerActor->getState() == Actor::State::Run) {
					player2Actor->setPosition(player2Actor->getPosition().x + 10, player2Actor->getPosition().y);
				}
				else if (playerActor->getDirection() == Actor::Direction::Left && playerActor->getState() == Actor::State::Run) {
					player2Actor->setPosition(player2Actor->getPosition().x - 10, player2Actor->getPosition().y);
				}
				//P2 runs into player 1
				if (player2Actor->getDirection() == Actor::Direction::Right && player2Actor->getState() == Actor::State::Run) {
					playerActor->setPosition(playerActor->getPosition().x + 10, playerActor->getPosition().y);
				}
				else if (player2Actor->getDirection() == Actor::Direction::Left && player2Actor->getState() == Actor::State::Run) {
					playerActor->setPosition(playerActor->getPosition().x - 10, playerActor->getPosition().y);
				}
				//this doesn't make that much sense
				if (playerActor->getDirection() == Actor::Direction::Right && player2Actor->getDirection() == Actor::Direction::Left) {
					if (playerActor->getState() == Actor::State::Run && player2Actor->getState() == Actor::State::Run) {
						playerActor->setState(Actor::State::Idle);
						if (playerActor->getPosition().x > player2Actor->getBoundingRect().left) {
							playerActor->setPosition(player2Actor->getBoundingRect().left - 5, playerActor->getPosition().y);
						}
						player2Actor->setState(Actor::State::Idle);
					}
				}
				//this also doesnt make much sense
				if (player2Actor->getDirection() == Actor::Direction::Right && playerActor->getDirection() == Actor::Direction::Left) {
					if (playerActor->getState() == Actor::State::Run && player2Actor->getState() == Actor::State::Run) {
						playerActor->setState(Actor::State::Idle);
						if (player2Actor->getPosition().x > playerActor->getBoundingRect().left) {
							player2Actor->setPosition(playerActor->getBoundingRect().left - 5, player2Actor->getPosition().y);
						}
						player2Actor->setState(Actor::State::Idle);
					}
				}



				//P1 attacks and hits
				if (playerActor->getState() == Actor::State::Attack1) {

					if (player2Actor->isBlocking) {
						player2Actor->activateShield();
						sounds.play(EffectID::Block);
						//depending on the direction of the player push them back
						if (player2Actor->getDirection() == Actor::Direction::Left) {
							player2Actor->setPosition(player2Actor->getPosition().x + 10, player2Actor->getPosition().y);
							player2Actor->shield.setPosition(player2Actor->shield.getPosition().x+10, player2Actor->shield.getPosition().y);
						}
						else { // player is facing right
							player2Actor->setPosition(player2Actor->getPosition().x - 10, player2Actor->getPosition().y);
							player2Actor->shield.setPosition(player2Actor->shield.getPosition().x - 10, player2Actor->shield.getPosition().y);
						}
					}
					else {
						player2Actor->setState(Actor::State::TakeHit);
						dealDamage("p2");
					}
				}
				if (playerActor->getState() == Actor::State::Attack2) {

					if (player2Actor->isBlocking) {
						player2Actor->activateShield();
						sounds.play(EffectID::Block);
						if (player2Actor->getDirection() == Actor::Direction::Left) {
							player2Actor->setPosition(player2Actor->getPosition().x + 10, player2Actor->getPosition().y);
							player2Actor->shield.setPosition(player2Actor->shield.getPosition().x + 10, player2Actor->shield.getPosition().y);
						}
						else { // player is facing right
							player2Actor->setPosition(player2Actor->getPosition().x - 10, player2Actor->getPosition().y);
							player2Actor->shield.setPosition(player2Actor->shield.getPosition().x - 10, player2Actor->shield.getPosition().y);
						}					
					}
					else {
						player2Actor->setState(Actor::State::TakeHit);
						dealDamage("p2");
					}
				}
				//P2 attacks and hits
				if (player2Actor->getState() == Actor::State::Attack1) {
					if (playerActor->isBlocking) {
						playerActor->activateShield();
						sounds.play(EffectID::Block);
						if (playerActor->getDirection() == Actor::Direction::Left) {
							playerActor->setPosition(playerActor->getPosition().x + 10, playerActor->getPosition().y);
							playerActor->shield.setPosition(playerActor->shield.getPosition().x + 10, playerActor->shield.getPosition().y);
						}
						else { // player is facing right
							playerActor->setPosition(playerActor->getPosition().x - 10, playerActor->getPosition().y);
							playerActor->shield.setPosition(playerActor->shield.getPosition().x - 10, playerActor->shield.getPosition().y);
						}					
					}
					else {
						playerActor->setState(Actor::State::TakeHit);
						dealDamage("p1");
					}			
				}
				if (player2Actor->getState() == Actor::State::Attack2) {

					if (playerActor->isBlocking) {
						playerActor->activateShield();
						sounds.play(EffectID::Block);
						if (playerActor->getDirection() == Actor::Direction::Left) {
							playerActor->setPosition(playerActor->getPosition().x + 10, playerActor->getPosition().y);
							playerActor->shield.setPosition(playerActor->shield.getPosition().x + 10, playerActor->shield.getPosition().y);
						}
						else { // player is facing right
							playerActor->setPosition(playerActor->getPosition().x - 10, playerActor->getPosition().y);
							playerActor->shield.setPosition(playerActor->shield.getPosition().x - 10, playerActor->shield.getPosition().y);
						}
					}
					else {
						playerActor->setState(Actor::State::TakeHit);
						dealDamage("p1");
					}
				}
			}
			
		}
	}
}





