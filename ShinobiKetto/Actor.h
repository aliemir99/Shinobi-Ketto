#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "ResourceIdentifier.h"
#include "Animation2.h"
#include "TextNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML\System\Clock.hpp>
#include "Category.h"
#include "SoundPlayer.h"
/*
    Team: 
    Date: 
    Purpose: 
*/
class Actor : public Entity
{
public:
    enum class Type {
        Hero1,
        Hero2,
        Hero3,
        Platform,

    };
    enum class State {
        Dead, Idle, Jump, 
        Attack1, Attack2, Fall, Run, TakeHit, Static, count
    };
    enum class Direction
    {
        Left, Right, Up, Down, Static
    };
public:

    bool								isJumping;
    bool								isFalling;
    bool                                isGrounded;
    const int							gravitySpeed;
    const int							groundHeight;
    float                               TimeThisJump;
    bool                                JustJumped = false;
    float                               JumpDuration;
    bool                                isBlocking = false;
    float                               shieldTimer;

    sf::Sprite                          shield;
    Actor(Type type, const TextureHolder_t& textures, const FontHolder_t& fonts, Category::Type player);
    ~Actor() = default;
    unsigned int                        getCategory() const override;
    sf::FloatRect                       getBoundingRect() const override;
    float                               getMaxSpeed() const;
    bool                                isMarkedForRemoval() const override;
    void                                setState(State state);
    Actor::State                        getState() const;
    Actor::Type                         getType() const;

    void                                playSound(EffectID effectType);

    void                                setIsJumping(bool jump);
    bool                                getIsJumping();

    void                                setDirection(Actor::Direction direction);
    Actor::Direction                    getDirection();

    bool                                isCurrentAnimationFinished();
    //will need a function to deactivate the shield.
    void                                deactivateShield();
    // will need a function that will activate the shield for the player in update states x amount of seconds  
    void                                activateShield();

private:
    void                                updateStates();
    void                                updateCurrent(sf::Time dt, CommandQueue& commands) override;
    void                                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void                                updateMovementPattern(sf::Time dt);
    void                                updateSounds();
    

private:
    Type                                type_;
    State                               state_;
    mutable sf::Sprite                  sprite_;
    std::map<Actor::State, Animation2>     animations_;
    Direction                           direction_;
    TextNode* healthDisplay_;
    float                               travelDistance_;
    std::size_t                         directionIndex_;

    float                               worldBounderiesWidth;
    Category::Type                      category;

    float                               countdown;
    sf::Time                            elapsedTime;
    sf::Clock                           clock;

    SoundPlayer                         soundplayer;

    bool                                canPlayDamageSound;

    sf::Texture                         shieldTexture;



};
