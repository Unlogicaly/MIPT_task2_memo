#include "create_window.h"
#include "wtypes.h"

void GetDesktopResolution(int &horizontal, int &vertical)
{
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    horizontal = desktop.right;
    vertical = desktop.bottom;
}

bool in(const std::string &obj, const std::vector<std::string> &src)
{
    for (auto &s : src)
    {
        if (obj == s)
            return true;
    }
    return false;
}

const std::vector<std::string> sizes{"max", "m", "half", "h", "quarter", "q"};

Simple_window *create_window(const std::string &size, bool with_grid, const Graph_lib::Point p,
                             const std::string &title, Fl_Color c)
{
    if (!in(size, sizes))
        throw std::runtime_error("Undefined size type");

    int w = 0, h = 0;
    GetDesktopResolution(w, h);

    if (in(size, {"half", "h"}))
    {
        w /= 2;
    }

    if (in(size, {"quarter", "q"}))
    {
        w /= 2;
        h /= 2;
    }

    auto win = new Simple_window{p, w, h, title};

    win->color(c);

    if (with_grid)
    {
        int x_tick = in(size, {"quarter", "q"}) ? 10 : 20;
        int y_tick = in(size, {"quarter", "q"}) ? 10 : 20;

        auto grid = new Grid{w, h, x_tick, y_tick, Graph_lib::Color::black, Graph_lib::Line_style::dot};

        win->attach(*grid);
    }
    return win;
}
