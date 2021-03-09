#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <memory>
#include <set>
#include "Category.h"
#include "Command.h"
//forward declaration

class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<SceneNode>;
	using Pair = std::pair<SceneNode*, SceneNode*>;
public:
	SceneNode(Category::Type c = Category::Type::None);

	void						attachChild(Ptr child);
	Ptr							detachChild(const SceneNode& node);

	virtual sf::FloatRect		getBoundingRect() const;
	void						update(sf::Time dt, CommandQueue& commands);

	sf::Vector2f				getWorldPosition() const;
	sf::Transform				getWorldTransform() const;

	void						onCommand(const Command& command, sf::Time dt);

	virtual unsigned int		getCategory() const;
	virtual bool				isDestroyed() const;
	virtual bool				isMarkedForRemoval()const;

	void						checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void						checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void						removeWrecks();
private:
	virtual void				updateCurrent(sf::Time dt, CommandQueue& commands);
	void						updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void						drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void						drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states)const;



private:

	std::vector<Ptr>			children;
	SceneNode* parent;
	Category::Type				defaultCategory;

};

float	calculateDistance(const SceneNode& lhs, const SceneNode& rhs);
bool	IsColliding(const SceneNode& lhs, const SceneNode& rhs);


