#include <raylib.h>
#include "Menu.h"
#include "Window.h"

#include <string>
#include <array>

void Menu::moveArrow(Window& w, Menu& m) {
    //moves the arrows up/down and loops back into itself
    switch (m.dir) {
    case 'u': m.prev = static_cast<int>(m.m_selection) - 1; if (m.prev >= static_cast<int>(m.start))
        m.m_selection = static_cast<Menu::Selection>(m.prev); break;
    case 'd': m.next = static_cast<int>(m.m_selection) + 1; if (m.next <= static_cast<int>(m.exit))
        m.m_selection = static_cast<Menu::Selection>(m.next); break;
    }
}

void Menu::drawMenuScreen(Window& w, Menu& m) {
    //i wrote this at like 2am and it hurts my head to even look at
    //basically i just append the arrow array to whatever enum
    //is currently loaded into the selection var
    std::string startText = m.m_selection == m.start
        ? TextJoin(std::array{ m.m_MenuArrowLeft.c_str(), m.m_MenuOptionStart.c_str(),
            m.m_MenuArrowRight.c_str() }.data(), 3, "  ") : m.m_MenuOptionStart;
    std::string settingsText = m.m_selection == m.settings
        ? TextJoin(std::array{ m.m_MenuArrowLeft.c_str(), m.m_MenuOptionSettings.c_str(),
            m.m_MenuArrowRight.c_str() }.data(), 3, "  ") : m.m_MenuOptionSettings;
    std::string exitText = m.m_selection == m.exit
        ? TextJoin(std::array{ m.m_MenuArrowLeft.c_str(), m.m_MenuOptionExit.c_str(),
            m.m_MenuArrowRight.c_str() }.data(), 3, "  ") : m.m_MenuOptionExit;

    int startWidth = MeasureText(startText.c_str(), w.m_fontSize);
    int settingsWidth = MeasureText(settingsText.c_str(), w.m_fontSize);
    int exitWidth = MeasureText(exitText.c_str(), w.m_fontSize);

    DrawText(startText.c_str(), w.centerX - startWidth / 2, w.centerY +
        m.selectionOffset - w.m_fontSize / 2, w.m_fontSize, WHITE);
    DrawText(settingsText.c_str(), w.centerX - settingsWidth / 2, w.centerY -
        w.m_fontSize / 2, w.m_fontSize, WHITE);
    DrawText(exitText.c_str(), w.centerX - exitWidth / 2, w.centerY -
        m.selectionOffset - w.m_fontSize / 2, w.m_fontSize, WHITE);
}

void Menu::checkMenuEvents(Window& w, Menu& m) {
    //user moves arr's up/down between menu options
    //settings not functional, only included bc i wanted more
    //menu options to flex this feature with bc it took way
    //too long to figure out lol
    m.key = static_cast<KeyboardKey>(GetKeyPressed());
    switch (m.key) {
    case KEY_W: m.dir = 'u'; moveArrow(w, m); break;
    case KEY_UP: m.dir = 'u'; moveArrow(w, m); break;
    case KEY_S: m.dir = 'd'; moveArrow(w, m); break;
    case KEY_DOWN: m.dir = 'd'; moveArrow(w, m); break;
    case KEY_ENTER: switch (m.m_selection) {
    case m.start: w.m_gameStarted = true; w.m_menuClosed = true;  break;
    case m.settings: break;
    case m.exit: w.m_isRunning = false; break;
    }
    }
}

void Menu::drawIntroText(Window& w, Menu& m) {
    float delta = GetFrameTime();

    //fade intro text in and hold for 2 seconds
    w.m_currentAlpha += w.m_introSpeed * delta;
    if (w.m_currentAlpha > w.m_maxAlpha) w.m_currentAlpha = w.m_maxAlpha;

    if (w.m_currentAlpha >= w.m_maxAlpha) {
        w.m_introHoldTimer += delta;
        if (w.m_introHoldTimer >= 2.0f) {
            w.m_introDone = true;
        }
    }

    //center text by calc width and font size
    Color textColor = Fade(WHITE, w.m_currentAlpha / w.m_maxAlpha);
    w.m_textWidth = MeasureText(w.m_introText.c_str(), w.m_fontSize);
    DrawText(w.m_introText.c_str(), w.centerX - w.m_textWidth / 2,
        w.centerY - w.m_fontSize / 2, w.m_fontSize, textColor);
    if (w.m_introDone) {
        w.m_menuClosed = false;
    }
}