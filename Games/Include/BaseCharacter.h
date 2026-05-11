// BaseCharacter.h
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class BaseCharacter
{
public:
    virtual ~BaseCharacter() = default; // Always a virtual destructor!

    virtual void ApplyDamage(float amount) = 0;
    virtual void Attack(BaseCharacter &target) = 0;

    virtual void Update(float dt) = 0;
    virtual void Draw(sf::RenderWindow &window) = 0;
};
