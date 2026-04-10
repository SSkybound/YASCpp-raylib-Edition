#ifndef WINDOW_H_4_7_26
#define WINDOW_H_4_7_26

#include <raylib.h>
#include <string>

struct Window {

    void DrawTextOutlined(const char* text, int x, int y, int fontSize, Color fill, Color outline);

    const int centerX{ 320 };
    const int centerY{ 240 };

    int m_monitorRefreshRate{};
    const int m_windowWidth{ 640 };
    const int m_windowHeight{ 480 };

    bool m_isRunning{ true };

    const std::string m_windowTitle{ "YASC++ RLE" };
    const std::string m_introText{ "YASC++" };
    const std::string m_introSubText{ "RayLib Edition" };

    int m_fontSize{ 20 };
    int m_textWidth{};

    const float m_introSpeed{ 100.0f };
    float m_currentAlpha{ 0.0f };
    const float m_maxAlpha{ 255.0f };
    float m_introHoldTimer{ 0.0f };
    bool m_introDone{ false };
    bool m_menuClosed{ true };
    bool m_gameStarted{ false };
};
#endif