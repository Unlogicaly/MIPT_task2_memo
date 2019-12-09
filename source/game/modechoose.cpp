#include "mywin.h"

modeChoose::modeChoose(myWin &win, Graph_lib::Callback cb_start)
    : Widget::Widget({win.x_max() / 2 - win.get_choose_mode_bs() * 3 / 2, win.y_max() / 2 - win.get_choose_mode_bs()},
                     3 * win.get_choose_mode_bs(), 2 * win.get_choose_mode_bs(), "",
                     [](Graph_lib::Address, Graph_lib::Address) {})
{
    for (auto n = 0; n < 6; ++n)
    {
        int x = n % 3 * win.get_choose_mode_bs() + (win.x_max() / 2 - win.get_choose_mode_bs() * 3 / 2);
        int y = n / 3 * win.get_choose_mode_bs() + (win.y_max() / 2 - win.get_choose_mode_bs());

        std::string name = std::to_string(modes[n].first) + "x" + std::to_string(modes[n].second);
        menu.push_back(
            new Graph_lib::Button{{x, y}, win.get_choose_mode_bs(), win.get_choose_mode_bs(), name, cb_start});
    }
}
