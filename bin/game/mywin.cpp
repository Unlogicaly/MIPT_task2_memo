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
}

void myWin::asc()
{
    //    play_ag = new playAgain(*this, cb_exit, cb_end);
    attach(*play_ag);
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
    fullscreen();

    exit_button = new Graph_lib::Button({x_resol - yes_no_bs, 0}, yes_no_bs, yes_no_bs, "Quit", cb_end);

    mode_ch = new modeChoose(*this, cb_start);

    play_ag = new playAgain(*this, cb_exit, cb_end);

    color(Graph_lib::Color::white);

    mode_ch = new modeChoose(*this, cb_start);

    attach(*mode_ch);

    while (!started and Fl::wait())
    {
    }

    calc_field_params(this);

    mode_ch->hide_menu();

    attach(*exit_button);

    Fl::redraw();
}

playAgain::playAgain(myWin &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end)
    : _size{win.get_choose_mode_bs()},
      win{win},
      asc{nullptr},
      yes_b{nullptr},
      yes_im{nullptr},
      no_b{nullptr},
      no_im{nullptr},
      back{nullptr},
      Widget::Widget({win.x_max() / 2 - _size, win.y_max() / 2 - _size * 7 / 6}, 2 * _size, _size * 5 / 3, "",
                     [](Graph_lib::Address, Graph_lib::Address) {})
{
    int w = win.x_max();
    int h = win.y_max();

    asc = new Graph_lib::Image({w / 2 - _size, h / 2 - _size * 7 / 6}, get_pic("asc", _size * 2 / 3, 2 * _size));
    yes_b = new Graph_lib::Button({w / 2 - _size, h / 2 - _size / 2}, _size, _size, "", cb_again);
    yes_im = new Graph_lib::Image({w / 2 - _size, h / 2 - _size / 2}, get_pic("yes", _size, _size));

    no_b = new Graph_lib::Button({w / 2, h / 2 - _size / 2}, _size, _size, "", cb_end);
    no_im = new Graph_lib::Image({w / 2, h / 2 - _size / 2}, get_pic("no", _size, _size));

    back = new Graph_lib::Rectangle({{w / 2 - _size, h / 2 - _size * 7 / 6}, 2 * _size, _size * 5 / 3});

    back->set_fill_color(Graph_lib::Color::white);
    back->set_color(Graph_lib::Color::white);
}
