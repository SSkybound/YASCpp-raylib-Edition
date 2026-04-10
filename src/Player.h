#ifndef PLAYER_H_4_9_26
#define PLAYER_H_4_9_26

#include <vector>

struct Body {
    int x{};
    int y{};
};

struct Player {

    enum Direction {
        north,
        east,
        south,
        west,
    };

    Direction m_dir{ east };
    Direction m_queuedDir{ east };

    std::vector<Body> snake{ {12, 12}, {11, 12}, {10, 12}, {9, 12} };
    std::vector<int> map{ std::vector<int>() };

    int m_tileSize{ 20 };
    int m_mapWidth{ 24 };
    int m_mapHeight{ 24 };
    int m_mapOffsetWidth{ 80 };
    int m_mapOffsetHeight{ 0 };

    int m_foodX{};
    int m_foodY{};

    int m_score{};

    int key{};
    bool m_inputReady{ true };
    bool m_isPaused{ false };
    bool m_isDead{ false };

    double m_tick{ 0.0 };

    Player() {
        map.resize(m_mapWidth * m_mapHeight);
    }
};

//decl death state to capture p member vars
extern Player g_deathState;

struct Window;

bool checkNoReverse(Player& p, Player::Direction reqDir);
void plrEvent(Player& p, Window& w);
void move(Player& p, Window& w);
void randomizeFood(Player& p);
void checkCanEat(Player& p);
void checkDeath(Player& p);
void triggerDeath(Player& p);

#endif