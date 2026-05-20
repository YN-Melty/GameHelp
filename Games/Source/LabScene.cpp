#include "LabScene.h"
#include "BaseCharacter.h"
#include "InputActions.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

using namespace LabScene;

Lab::Lab(EngineContext &context) : Scene(context), crossupTimer(0.0f), finalBoss(context), player(context), backgroundSprite(backgroundTexture)
{
    InitBackground();
    InitChar();
}

void Lab::InitChar()
{
    player.initChar();
    finalBoss.initChar();
}

void Lab::InitBackground()
{
    if (!backgroundTexture.loadFromFile(BackgroundPath))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture, true);

    float scaleX = static_cast<float>(gConfig.windowSize.x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(gConfig.windowSize.y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale({scaleX, scaleY});

    backgroundSprite.setColor(sf::Color::White);

    backgroundSprite.setPosition({0.f, 0.f}); // Top-left corner
}

void Lab::Start()
{
    ctx.cursor.SetVisible(false);

    ctx.input.Bind(ACTION_MOVE_LEFT, Input::Keyboard{sf::Keyboard::Scan::A});
    ctx.input.Bind(ACTION_MOVE_RIGHT, Input::Keyboard{sf::Keyboard::Scan::D});
    ctx.input.Bind(ACTION_JUMP, Input::Keyboard{sf::Keyboard::Scan::W});
    ctx.input.Bind(ACTION_CROUCH, Input::Keyboard{sf::Keyboard::Scan::S});
}

void Lab::Update()
{

    float dt = ctx.time.GetDeltaTime();
    float gravity = 800.f;

    float windowWidth = gConfig.windowSize.x;
    float windowHeight = gConfig.windowSize.y;
    float LEFT_WALL = 10.f, RIGHT_WALL = windowWidth - 10.f;
    float CEILING = 10.f, FLOOR = windowHeight - 100.f;

    player.pcAction(ctx.input, dt, gravity, player.playerHitBox, LEFT_WALL, RIGHT_WALL, CEILING, FLOOR);
    player.playerHitBox.setPosition(player.sprite.getPosition());

    finalBoss.EnemyAction(dt, gravity, finalBoss.getHitBox(), LEFT_WALL, RIGHT_WALL, CEILING, FLOOR);
    finalBoss.setHitBoxToSprite();

    BaseCharacter::fightersAntiCollision(player, finalBoss);
    player.lastX = player.getHitBox().getPosition().x;
    finalBoss.lastX = finalBoss.getHitBox().getPosition().x;
}
void Lab::Render() const
{

    ctx.renderer.Draw(backgroundSprite);
    ctx.renderer.Draw(player.sprite);
    ctx.renderer.Draw(player.playerHitBox);
    ctx.renderer.Draw(finalBoss.getSprite());
    ctx.renderer.Draw(finalBoss.getHitBox());
}

/* void Lab::fightersAntiCollision(PlayerCharacter &player, FinalBoss &boss)
{
    float playerHalfWidth = player.playerHitBox.getSize().x / 2.f;
    float playerHalfHeight = player.playerHitBox.getSize().y / 2.f;
    float bossHalfWidth = boss.getHitBox().getSize().x / 2.f;
    float bossHalfHeight = boss.getHitBox().getSize().y / 2.f;

    sf::Vector2f playerPos = player.playerHitBox.getPosition();
    sf::Vector2f bossPos = boss.getHitBox().getPosition();

    float playerLeft = playerPos.x - playerHalfWidth;
    float playerRight = playerPos.x + playerHalfWidth;
    float playerTop = playerPos.y - playerHalfHeight;
    float playerBottom = playerPos.y + playerHalfHeight;

    float bossLeft = bossPos.x - bossHalfWidth;
    float bossRight = bossPos.x + bossHalfWidth;
    float bossTop = bossPos.y - bossHalfHeight;
    float bossBottom = bossPos.y + bossHalfHeight;

    bool xOverlap = playerRight > bossLeft && playerLeft < bossRight;
    bool yOverlap = playerBottom > bossTop && playerTop < bossBottom;

    int unstuckTimer = 300; // 16.67

    if (xOverlap && yOverlap)
    {
        float overlapX = std::min(playerRight, bossRight) - std::max(playerLeft, bossLeft);
        float overlapY = std::min(playerBottom, bossBottom) - std::max(playerTop, bossTop);

        const float onTopThreshold = 0.8f;
        const float edgeBuffer = 8.0f;
        const float slowPushFactor = 0.05f; // Tweak for faster/slower push

        bool playerOnTop = (playerTop < bossTop) &&
                           (overlapY < overlapX * onTopThreshold) &&
                           (std::abs(playerBottom - bossTop) < edgeBuffer);

        bool bossOnTop = (bossTop < playerTop) &&
                         (overlapY < overlapX * onTopThreshold) &&
                         (std::abs(bossBottom - playerTop) < edgeBuffer);

        if (playerOnTop)
        {

            player.restartTimer();
            float slowPush = overlapX * slowPushFactor;
            if (playerPos.x < bossPos.x)
                boss.getSprite().move({slowPush, 0.f});
            else

                boss.getSprite().move({-slowPush, 0.f});
            boss.getHitBox().setPosition(boss.getSprite().getPosition());

            if (playerOnTop && player.getTime().asMilliseconds() > unstuckTimer)
            {
            }
        }
        else if (bossOnTop)
        {
            float slowPush = overlapX * slowPushFactor;
            if (bossPos.x < playerPos.x)
                player.sprite.move({slowPush, 0.f});
            else
                player.sprite.move({-slowPush, 0.f});
            player.playerHitBox.setPosition(player.sprite.getPosition());
        }
        else
        {
            if (overlapX < overlapY)
            {
                bool playerToLeft = playerPos.x < bossPos.x;
                float pushAmount = overlapX / 2.f;
                if (playerToLeft)
                {
                    player.sprite.move({-pushAmount, 0.f});
                    boss.getSprite().move({pushAmount, 0.f});
                }
                else
                {
                    player.sprite.move({pushAmount, 0.f});
                    boss.getSprite().move({-pushAmount, 0.f});
                }
            }
            else
            {
                bool playerAbove = playerPos.y < bossPos.y;
                float pushAmount = overlapY / 2.f;
                if (playerAbove)
                {
                    player.sprite.move({0.f, -pushAmount});
                    boss.getSprite().move({0.f, pushAmount});
                }
                else
                {
                    player.sprite.move({0.f, pushAmount});
                    boss.getSprite().move({0.f, -pushAmount});
                }
            }
            player.playerHitBox.setPosition(player.sprite.getPosition());
            boss.getHitBox().setPosition(boss.getSprite().getPosition());
        }
    }
}
*/
void Lab::OnPause(bool paused)
{
}
void Lab::OnCleanup()
{
}