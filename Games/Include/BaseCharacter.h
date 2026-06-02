#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class BaseCharacter
{
    sf::Clock collisionTimer;
    bool isTouching = false;

public:
    float lastX = 0.0f;

    int HP, MaxHP, Meter, MaxMeter;

    float getHP() { return HP; }
    float getMaxHP() { return MaxHP; }
    void setHP(float set) { HP = set; }
    void setMaxHP(float set) { MaxHP = set; }

    float getMeter() { return Meter; }
    float getMaxMeter() { return MaxMeter; }
    void setMaxMeter(float set) { MaxMeter = set; }
    void setMeter(float set) { Meter = set; }

    virtual ~BaseCharacter() = default;
    virtual sf::RectangleShape &getHitBox() = 0;

    virtual void ApplyDamage(float amount) = 0;
    virtual void Attack(BaseCharacter &target) = 0;

    virtual void Update(float dt) = 0;
    virtual void Draw(sf::RenderWindow &window) = 0;

    virtual sf::Sprite &getSprite() = 0;

    static bool isHitboxOverlapping(const sf::RectangleShape &a, const sf::RectangleShape &b);

    static void fightersAntiCollision(BaseCharacter &player, BaseCharacter &enemy);
    sf::Time restartTimer();
    sf::Time getTime() const;

    void isTouchingTrue();
    void isTouchingFalse();

    virtual bool isGrounded() const = 0;
};
