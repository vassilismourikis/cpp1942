#include "Game.h"
#include "configure.h"


// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->update();



}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game game;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "1939");

    graphics::setUserData(&game);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(1200, 600);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    game.init();
    

    graphics::startMessageLoop();

    return 0;
}