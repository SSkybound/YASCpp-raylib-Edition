#include "Window.h"
#include <raylib.h>

//raylib doesn't support txt outlining so i had to do it myself
//hope it's not too hacky of a fix
void Window::DrawTextOutlined(const char* text, int x, int y, int fontSize, Color fill, Color outline) {
	//offset center by text size and measure
	x = x - MeasureText(text, m_fontSize) / 2;
	y = y - m_fontSize / 2;
	
	DrawText(text, x - 1, y, fontSize, outline);
	DrawText(text, x + 1, y, fontSize, outline);
	DrawText(text, x, y - 1, fontSize, outline);
	DrawText(text, x, y + 1, fontSize, outline);

	DrawText(text, x, y, fontSize, fill);
}