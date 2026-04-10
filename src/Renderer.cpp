#include "raylib.h"
#include "Renderer.h"
#include "Player.h"
#include "Window.h"

#include <string>

void drawMap(Player& p, Window& w) {
    for (int x{}; x < p.m_mapWidth; ++x) {
        for (int y{}; y < p.m_mapHeight; ++y) {

            //search for head, body
            bool isBody{ false };
            bool isHead{ false };
            for (const auto& segment : p.snake) {
                if (p.snake[0].x == x && p.snake[0].y == y) {
                    isHead = true; break;
                }
                if (segment.x == x && segment.y == y) {
                    isBody = true; break;
                }
            }

            //draw white tiles, green body and blue head
            DrawRectangle(p.m_mapOffsetWidth + x * p.m_tileSize,
                p.m_mapOffsetHeight + y * p.m_tileSize,
                p.m_tileSize, p.m_tileSize, isBody ? GREEN : isHead ? SKYBLUE : WHITE);

            //draw food to map where food matches index
            bool isFood = (p.m_foodX == x && p.m_foodY == y);

            if (isFood) {
                DrawRectangle(p.m_mapOffsetWidth + x * p.m_tileSize,
                    p.m_mapOffsetHeight + y * p.m_tileSize,
                    p.m_tileSize, p.m_tileSize, RED);
            }

            //draw gridlines
            DrawRectangleLines(p.m_mapOffsetWidth + x * p.m_tileSize,
                p.m_mapOffsetHeight + y * p.m_tileSize,
                p.m_tileSize, p.m_tileSize, BLACK);

        }
    }
}

void drawDeathMap(Player& p, Window& w, int redUpTo) {
    for (int x{}; x < p.m_mapWidth; ++x) {
        for (int y{}; y < p.m_mapHeight; ++y) {

            //replacement draw loop for when the game ends, turn the snake body
            //red using the animation state from gameLoop for dramatic effect
            int segIndex{ -1 };
            for (int i{}; i < (int)p.snake.size(); ++i) {
                if (p.snake[i].x == x && p.snake[i].y == y) {
                    segIndex = i;
                    break;
                }
            }

            Color tileColor = WHITE;
            if (segIndex >= 0 && segIndex <= redUpTo) tileColor = RED;
            else if (segIndex == 0)                        tileColor = SKYBLUE;
            else if (segIndex > 0)                        tileColor = GREEN;

            DrawRectangle(p.m_mapOffsetWidth + x * p.m_tileSize,
                p.m_mapOffsetHeight + y * p.m_tileSize,
                p.m_tileSize, p.m_tileSize, tileColor);

            DrawRectangleLines(p.m_mapOffsetWidth + x * p.m_tileSize,
                p.m_mapOffsetHeight + y * p.m_tileSize,
                p.m_tileSize, p.m_tileSize, BLACK);
        }
    }
}

void drawEndScreen(Window& w, const Player& deathState) {
    ClearBackground(BLACK);
    //draws the map without red snake animation
    drawMap(const_cast<Player&>(deathState), w);

    //calc center of map
    int mapCenterX = deathState.m_mapOffsetWidth + (deathState.m_mapWidth * deathState.m_tileSize) / 2;
    int mapCenterY = deathState.m_mapOffsetHeight + (deathState.m_mapHeight * deathState.m_tileSize) / 2;

    //store as string so we can use c_str
    std::string scoreStr = "Score: " + std::to_string(deathState.m_score);

    //more custom outlined draw text
    w.DrawTextOutlined("Game Over", mapCenterX, mapCenterY - w.m_fontSize * 2, w.m_fontSize, RED, BLACK);
    w.DrawTextOutlined(scoreStr.c_str(), mapCenterX, mapCenterY - w.m_fontSize, w.m_fontSize, WHITE, BLACK);
    w.DrawTextOutlined("R   - Restart", mapCenterX, mapCenterY + w.m_fontSize, w.m_fontSize, ORANGE, BLACK);
    w.DrawTextOutlined("ESC - Menu", mapCenterX, mapCenterY + w.m_fontSize * 2, w.m_fontSize, ORANGE, BLACK);
}

void drawHUD(Player& p, Window& w) {
    std::string scoreStr = std::to_string(p.m_score);

    //clears the left margin to prevent score overlap
    DrawRectangle(0, 0, p.m_mapOffsetWidth, p.m_mapHeight * p.m_tileSize, BLACK);

    w.DrawTextOutlined("SCORE",
        p.m_mapOffsetWidth / 2,
        w.m_fontSize,
        w.m_fontSize, GRAY, BLACK);

    w.DrawTextOutlined(scoreStr.c_str(),
        p.m_mapOffsetWidth / 2,
        w.m_fontSize * 3,
        w.m_fontSize, WHITE, BLACK);
}