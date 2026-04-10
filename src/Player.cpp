#include "raylib.h"
#include "Player.h"
#include "Window.h"

//definition of death state to capture p member vars
Player g_deathState{};

bool checkNoReverse(Player& p, Player::Direction reqDir) {
    //make sure req dir is valid e.g snake cannot move back into itself
    if (p.m_dir == p.south && reqDir == p.north) {
        return false;
    }
    else if (p.m_dir == p.north && reqDir == p.south) {
        return false;
    }
    else if (p.m_dir == p.east && reqDir == p.west) {
        return false;
    }
    else if (p.m_dir == p.west && reqDir == p.east) {
        return false;
    }
    else {
        return true;
    }
}

void plrEvent(Player& p, Window& w) {
    //checks if input is ready to buffer inputs
    if (!p.m_inputReady) return;
    p.key = GetKeyPressed();

    //if no key was pressed just skip
    if (p.key == 0) return;

    Player::Direction reqDir = p.m_dir;
    switch (p.key) {
    case KEY_W: case KEY_UP: reqDir = p.north; break;
    case KEY_D: case KEY_RIGHT: reqDir = p.east; break;
    case KEY_S: case KEY_DOWN: reqDir = p.south; break;
    case KEY_A: case KEY_LEFT: reqDir = p.west; break;
    case KEY_P: p.m_isPaused = !p.m_isPaused;
    }

    //check if req dir is valid then buffer input
    if (checkNoReverse(p, reqDir)) {
        p.m_queuedDir = reqDir;
        p.m_inputReady = false;
    }
}

void move(Player& p, Window& w) {

    //loads queued dir into active dir
    if (GetTime() >= p.m_tick) {
        p.m_tick = GetTime() + 0.25;
        p.m_inputReady = true;
        p.m_dir = p.m_queuedDir;

        //move body along path
        for (int i = (int)p.snake.size() - 1; i > 0; --i) {
            p.snake[i] = p.snake[i - 1];
        }

        //move into active dir
        switch (p.m_dir) {
        case p.north: --p.snake[0].y; break;
        case p.south: ++p.snake[0].y; break;
        case p.east: ++p.snake[0].x; break;
        case p.west: --p.snake[0].x; break;
        }
    }
}

void randomizeFood(Player& p) {
    bool validPlacement{ false };

    while (!validPlacement) {
        //place food on grid
        p.m_foodX = GetRandomValue(0, p.m_mapWidth - 1);
        p.m_foodY = GetRandomValue(0, p.m_mapHeight - 1);

        //ensure food placement isn't on snake body
        validPlacement = true;
        for (int i{}; i < (int)p.snake.size(); ++i) {
            if (p.m_foodX == p.snake[i].x && p.m_foodY == p.snake[i].y) {
                validPlacement = false;
                break;
            }
        }
    }
    //store map index for m_food
}

void checkCanEat(Player& p) {
    //check if the player x/y == food x/y
        if (p.snake[0].x == p.m_foodX && p.snake[0].y == p.m_foodY) {
            ++p.m_score;
            p.snake.push_back(p.snake.back());
            randomizeFood(p);
        }
}

void checkDeath(Player& p) {
    //check if wall collision
    if (p.snake[0].x < 0 || p.snake[0].x >= p.m_mapWidth ||
        p.snake[0].y < 0 || p.snake[0].y >= p.m_mapHeight) {
        p.m_isDead = true;
    }
    //check if head has collided with body
    for (int i = 1; i < (int)p.snake.size(); ++i) {
        if (p.snake[0].x == p.snake[i].x && p.snake[0].y == p.snake[i].y) {
            p.m_isDead = true;
            break;
        }
    }
}

void triggerDeath(Player& p) {
    //snap a 'screenshot' of p to show on end screen
    g_deathState = p;
}