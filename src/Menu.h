#ifndef MENU_H_4_7_26
#define MENU_H_4_7_26

#include <string>

struct Window;

struct Menu {

    enum Selection {
        start,
        settings,
        exit,
    };

    void drawIntroText(Window& w, Menu& m);
    void checkMenuEvents(Window& w, Menu& m);
    void drawMenuScreen(Window& w, Menu& m);
    void moveArrow(Window& w, Menu& m);


    Selection m_selection{ start };

    std::string m_MenuOptionStart{ "Start Game" };
    std::string m_MenuOptionExit{ "Exit" };
    std::string m_MenuOptionSettings{ "Settings" };

    std::string m_MenuArrowLeft{ ">" };
    std::string m_MenuArrowRight{ "<" };

    int selectionOffset{ -50 };
    int next{};
    int prev{};

    char dir{};
    int key{};
};
#endif