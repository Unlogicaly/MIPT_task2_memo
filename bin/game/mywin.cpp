#include "mywin.h"

modeChoose::modeChoose(Graph_lib::Window &win, Graph_lib::Callback cb_start)
    : Widget::Widget({1920 / 2 - 260, 1080 / 2 - 170}, 520, 340, "", [](Graph_lib::Address, Graph_lib::Address) {}),
      win{win}
{
    for (auto n = 0; n < 6; ++n)
    {
        int x = n % 3 * 160 + (1920 / 2 - 260);
        int y = n / 3 * 160 + (1080 / 2 - 170);
        std::string name = std::to_string(modes[n].first) + "x" + std::to_string(modes[n].second);
        menu.push_back(new Graph_lib::Button{{x, y}, 160, 160, name, cb_start});
    }
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

myWin::myWin(bool &end)
    : Window({0, 0}, 1920, 1080, ""),
      exit_button({x_max() - 70, 20}, 70, 20, "Quit", cb_exit),
      mode_ch(nullptr),
      play_ag{new playAgain(*this, cb_exit, cb_end)},
      end{end}
{
    color(Graph_lib::Color::white);

    mode_ch = new modeChoose(*this, cb_start);

    while (!started and Fl::wait())
    {
    }

    mode_ch->hide_menu();

    attach(exit_button);
    attach(*play_ag);
    play_ag->attach(*this);

    play_ag->hide_q();

    Fl::redraw();
}

playAgain::playAgain(Graph_lib::Window &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end)
    : win{win},
      asc{new Graph_lib::Text({1920 / 2 - 60, 1920 / 2 - 50}, "Play again?")},
      yes{new Graph_lib::Button({1920 / 2 - 100, 1920 / 2 - 50}, 100, 100, "Yes", cb_again)},
      no{new Graph_lib::Button({1920 / 2, 1920 / 2 - 50}, 100, 100, "No", cb_end)},
      Widget::Widget({1920 / 2 - 100, 1920 / 2 - 66}, 200, 116, "", [](Graph_lib::Address, Graph_lib::Address) {})
{
    asc->set_font(Graph_lib::Font::courier);
    asc->set_font_size(16);
}
