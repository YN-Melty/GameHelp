#include "LabScene.h"

using namespace LabScene;

Lab::Lab(EngineContext &context) : Scene(context)
{
}

void Lab::Start()
{
    ctx.cursor.SetVisible(false);

    balls.clear();

    StartPaddle();
    StartStats();
    StartMusic();

    ballSpawnCooldown.Restart();
}

void Lab::Update()
{
    if (ballSpawnCooldown.IsOver())
    {
        EventBallSpawn();
        ballSpawnCooldown.Restart();
    }

    UpdatePaddle();
    UpdateBalls();

    HandleCollisions();
}
void Lab::Render() const
{
    ctx.renderer.Draw(background);

    ctx.renderer.Draw(paddle.shape);

    for (const auto &ball : balls)
    {
        ctx.renderer.Draw(ball.shape);
    }

    ctx.renderer.Draw(stats.scoreText);
    ctx.renderer.Draw(stats.highScoreText);
    ctx.renderer.Draw(stats.livesText);
}
void Lab::OnPause(bool paused)
{
    if (paused)
    {
        ballSpawnCooldown.Stop();
        music.pause();
        bounceSound.stop();
    }
    else
    {
        ballSpawnCooldown.Start();
        music.play();
    }
}
void Lab::OnCleanup()
{
    music.stop();
    bounceSound.stop();
}