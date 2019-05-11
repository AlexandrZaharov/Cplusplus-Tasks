#pragma once

#include "world.h"
#include "window.h"
#include "message_box.h"


class Game
{
public:
    Game();
    virtual ~Game() = default;

    void Run();
    void HandleInput();
    void Update(const float dt);
    void Render();


private:

    Window main_window_;
    World world_;
    MessageBox message_box_;
};
