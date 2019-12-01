#include "mywin.h"
#include "wtypes.h"

modeChoose::modeChoose(myWin &win, Graph_lib::Callback cb_start)
    : Widget::Widget({win.x_max() / 2 - win.get_choose_mode_bs() * 3 / 2, win.y_max() / 2 - win.get_choose_mode_bs()},
                     3 * win.get_choose_mode_bs(), 2 * win.get_choose_mode_bs(), "",
                     [](Graph_lib::Address, Graph_lib::Address) {}),
      win{win}
{
    for (auto n = 0; n < 6; ++n)
    {
        int x = n % 3 * win.get_choose_mode_bs() + (win.x_max() / 2 - win.get_choose_mode_bs() * 3 / 2);
        int y = n / 3 * win.get_choose_mode_bs() + (win.y_max() / 2 - win.get_choose_mode_bs());
        std::string name = std::to_string(modes[n].first) + "x" + std::to_string(modes[n].second);
        menu.push_back(
            new Graph_lib::Button{{x, y}, win.get_choose_mode_bs(), win.get_choose_mode_bs(), name, cb_start});
    }
    attach(win);
}

std::pair<int, int> convert(myWin &win, int n, int m, bool reverse)
{
    if (!reverse)
    {
        return {n * win.get_choose_mode_bs() + win.x_max() / 2 - 260, m * win.get_choose_mode_bs() + 1080 / 2 - 170};
    }
    else
        return {(n - win.x_max() / 2 + 260) / win.get_choose_mode_bs(),
                (m - 1080 / 2 + 170) / win.get_choose_mode_bs()};
}

void myWin::asc()
{
    play_ag->show_q();
}

int calc_choose_mode_bs(int, int y_resol)
{
    return y_resol / 6;
}

int calc_yes_no_bs(int, int y_resol)
{
    return y_resol / 10;
}

void calc_field_params(myWin *win)
{
    win->set_size(win->y_max() / (win->get_height() + 1));
    win->set_shift(win->get_size() / 20);
    win->set_side_gap((win->x_max() - win->get_size() * win->get_width()) / 2);
    win->set_up_gap((win->y_max() - win->get_size() * win->get_height()) / 2);
}

myWin::myWin(bool &end, int x_resol, int y_resol)
    : Window({0, 0}, x_resol, y_resol, ""),
      exit_button(nullptr),
      mode_ch(nullptr),
      play_ag{nullptr},
      choose_mode_bs{calc_choose_mode_bs(x_resol, y_resol)},
      yes_no_bs{calc_yes_no_bs(x_resol, y_resol)},
      end{end}
{
    exit_button = new Graph_lib::Button({x_resol - yes_no_bs, 0}, yes_no_bs, yes_no_bs, "Quit", cb_end);

    mode_ch = new modeChoose(*this, cb_start);

    play_ag = new playAgain(*this, cb_exit, cb_end);

    color(Graph_lib::Color::white);

    mode_ch = new modeChoose(*this, cb_start);

    while (!started and Fl::wait())
    {
    }

    calc_field_params(this);

    mode_ch->hide_menu();

    attach(*exit_button);
    attach(*play_ag);

    play_ag->hide_q();

    Fl::redraw();
}

playAgain::playAgain(Graph_lib::Window &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end)
    : win{win},
      asc{new Graph_lib::Text({win.x_max() / 2 - 60, win.y_max() / 2 - 50}, "Play again?")},
      yes{new Graph_lib::Button({win.x_max() / 2 - 100, win.y_max() / 2 - 50}, 100, 100, "Yes", cb_again)},
      no{new Graph_lib::Button({win.x_max() / 2, win.y_max() / 2 - 50}, 100, 100, "No", cb_end)},
      Widget::Widget({win.x_max() / 2 - 100, win.y_max() / 2 - 66}, 200, 116, "",
                     [](Graph_lib::Address, Graph_lib::Address) {})
{
    asc->set_font(Graph_lib::Font::courier);
    asc->set_font_size(16);
}
