#include "field.h"
#include <algorithm>
#include <chrono>
#include <wtypes.h>

void get_desktop_resolution(int &horizontal, int &vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

template <class T>
void print(const std::vector<T> &src, const std::string &sep = " ", const std::string &end = "\n",
           std::ostream &os = std::cout)
{
    for (auto &t : src)
    {
        os << t << sep;
    }
    os << end;
}

void launch()
{
    int w, h;
    get_desktop_resolution(w, h);

    bool end = false;
    while (!end)
    {
        Field f(end, w, h);
        Graph_lib::gui_main();
    }
}

int main()
{
    Graph_lib::Font font(Graph_lib::Font::courier);

    launch();

    clear();

    return Graph_lib::gui_main();
}
