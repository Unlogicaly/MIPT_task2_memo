#include "game_start.h"
#include <wtypes.h>

void get_desktop_resolution(int &horizontal, int &vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom - 50;
}

void launch()
{
    int w, h;
    get_desktop_resolution(w, h);

    bool end = false;
    while (!end)
    {
        clear();
        Field f(end, w, h);
        Graph_lib::gui_main();
    }
    clear();
}
