#ifndef RENDERER_H_4_9_26
#define RENDERER_H_4_9_26

struct Player;
struct Window;

void drawMap(Player& p, Window& w);
void drawDeathMap(Player& p, Window& w, int redUpTo);
void drawEndScreen(Window& w, const Player& deathState);
void drawHUD(Player& p, Window& w);

#endif