#include "raylib.h"
#include "GameLoop.h"
#include "Menu.h"
#include "Window.h"
#include "Player.h"
#include "Renderer.h"

void gameLoop(Window& w, Menu& m, Player& p) {

    int    m_deathAnimIndex{ 0 };
    double m_deathAnimTick{ 0.0 };

    while (w.m_isRunning && !WindowShouldClose()) {

        BeginDrawing();

        if (!w.m_introDone) {
            m.drawIntroText(w, m);
            ClearBackground(BLACK);
        }
        if (!w.m_menuClosed) {
            m.drawMenuScreen(w, m);
            m.checkMenuEvents(w, m);
            ClearBackground(BLACK);
        }

        if (w.m_gameStarted) {

            if (p.m_isDead) {
                bool animDone = m_deathAnimIndex >= (int)g_deathState.snake.size();

                if (!animDone) {
                    ClearBackground(BLACK);
                    drawDeathMap(g_deathState, w, m_deathAnimIndex);
                    if (GetTime() >= m_deathAnimTick) {
                        m_deathAnimTick = GetTime() + 0.08;
                        ++m_deathAnimIndex;
                    }
                }
                else {
                    drawEndScreen(w, g_deathState);
                }

                //let plr cancel death animation early
                if (IsKeyPressed(KEY_R)) {
                    p = Player{};
                    randomizeFood(p);
                    m_deathAnimIndex = 0;
                    m_deathAnimTick = 0.0;
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    p = Player{};
                    randomizeFood(p);
                    w.m_gameStarted = false;
                    w.m_menuClosed = false;
                    m_deathAnimIndex = 0;
                    m_deathAnimTick = 0.0;
                }
            }
            else if (p.m_isPaused) {
                p.m_inputReady = true;
                drawMap(p, w);
                plrEvent(p, w);
                w.DrawTextOutlined("Paused", w.centerX, w.centerY, w.m_fontSize, ORANGE, BLACK);
            }
            else {
                checkCanEat(p);
                drawMap(p, w);
                drawHUD(p, w);
                plrEvent(p, w);
                move(p, w);
                checkDeath(p);

                if (p.m_isDead) {
                    triggerDeath(p);

                    //if the death happened due to border collision, reset snake
                    //position of the head to show plr where they died &&
                    //push back the body 1 tile to show where body was at death
                    if (g_deathState.snake[0].x < 0 || g_deathState.snake[0].x >= g_deathState.m_mapWidth ||
                        g_deathState.snake[0].y < 0 || g_deathState.snake[0].y >= g_deathState.m_mapHeight) {
                        for (int i = 0; i < (int)g_deathState.snake.size() - 1; ++i) {
                            g_deathState.snake[i] = g_deathState.snake[i + 1];
                        }
                    }

                    m_deathAnimTick = GetTime() + 0.08;
                }
            }
        }

        EndDrawing();
    }

    //cleanup on menu exit || user window closed
    CloseWindow();
}