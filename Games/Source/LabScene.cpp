#include "LabScene.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

using namespace LabScene;

Lab::Lab(EngineContext &context) : Scene(context)
{
    Lab::InitBackground();
    Lab::InitChar();
}

void Lab::InitChar()
{
    playerHitBox.setSize({64.f, 96.f});                   // width, height
    playerHitBox.setOrigin(playerHitBox.getSize() / 2.f); // center it (optional)
    playerHitBox.setPosition({200.f, 200.f});             // spawn position

    playerHitBox.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent fill
    playerHitBox.setOutlineColor(sf::Color::Green);   // border color
    playerHitBox.setOutlineThickness(2.f);            // border thickness
}

void Lab::InitBackground()
{
    background.setTexture(ctx.resources.FetchTexture(PlayerStatsConfig::BackgroundTexture));
    background.setSize(gConfig.windowSize);
}

void Lab::Start()
{
    ctx.cursor.SetVisible(false);
}

void Lab::Update()
{
}
void Lab::Render() const
{

    ctx.renderer.Draw(background);
    ctx.renderer.Draw(playerHitBox);

    /* ctx.renderer.Draw(background);

     ctx.renderer.Draw(paddle.shape);

     for (const auto &ball : balls)
     {
         ctx.renderer.Draw(ball.shape);
     }

     ctx.renderer.Draw(stats.scoreText);
     ctx.renderer.Draw(stats.highScoreText);
     ctx.renderer.Draw(stats.livesText);
     */
}
void Lab::OnPause(bool paused)
{
}
void Lab::OnCleanup()
{
}