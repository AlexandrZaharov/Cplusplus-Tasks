#pragma once
#include <iostream>
#include <vector>
#include "forest.h"
#include "window.h"

//class Window;


class Game
{
public:
    Game();
    virtual ~Game() = default;

    void Run();
    void Update();
    void Render();
    void HandleInput();

private:

    Forest forest_;
    Window main_window_;
};
