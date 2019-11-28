#include "mywin.h"

modeChoose::modeChoose(Graph_lib::Window &win, Graph_lib::Callback cb_start)
    : Widget::Widget({1920 / 2 - 260, 1080 / 2 - 170}, 520, 340, "", [](Graph_lib::Address, Graph_lib::Address) {})
{
    for (auto n = 0; n < 6; ++n)
    {
        int x = n % 3 * 160 + (1920 / 2 - 260);
        int y = n / 3 * 160 + (1080 / 2 - 170);
        std::string name = std::to_string(modes[n].first) + "x" + std::to_string(modes[n].second);
        menu.push_back(new Graph_lib::Button{{x, y}, 160, 160, name, cb_start});
    }
    std::cerr << menu.size() << std::endl;
    attach(win);
}

std::pair<int, int> convert(int n, int m, bool reverse)
{
    if (!reverse)
    {
        return {n * mbs + 1920 / 2 - 260, m * mbs + 1080 / 2 - 170};
    }
    else
        return {(n - 1920 / 2 + 260) / mbs, (m - 1080 / 2 + 170) / mbs};
}

myWin::myWin() : Window({0, 0}, 1920, 1080, ""), exit_button({x_max() - 70, 20}, 70, 20, "Quit", cb_exit), menu(nullptr)
{
    color(Graph_lib::Color::white);

    menu = new modeChoose(*this, cb_start);

    attach(exit_button);

    while (!started and Fl::wait())
    {
    }

    menu->hide_menu();
    std::cerr << __LINE__ << std::endl;
    attach(exit_button);
    Fl::redraw();
}
