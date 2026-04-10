#include "raylib.h"
#include "Menu.h"
#include "Window.h"
#include "Player.h"
#include "GameLoop.h"

#include <memory>
#include <ctime>

int main() {
    //decl ptrs
    std::unique_ptr<Window> w{ new Window };
    std::unique_ptr<Menu> m{ new Menu };
    std::unique_ptr<Player> p{ new Player };

    //set 'random' seed based on time && place food
    SetRandomSeed(static_cast<unsigned int>(time(nullptr)));
    randomizeFood(*p);

    //start window, sync fps to monitor hertz
    InitWindow(w->m_windowWidth, w->m_windowHeight, w->m_windowTitle.c_str());
    SetExitKey(KEY_NULL);
    SetTargetFPS(GetMonitorRefreshRate(0));

    //begin game looping
    gameLoop(*w, *m, *p);
    return 0;
}