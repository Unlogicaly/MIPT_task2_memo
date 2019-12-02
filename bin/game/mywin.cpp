#include "mywin.h"
#include "wtypes.h"

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
      new_button{nullptr},
      mode_ch(nullptr),
      play_ag{nullptr},
      choose_mode_bs{calc_choose_mode_bs(x_resol, y_resol)},
      yes_no_bs{calc_yes_no_bs(x_resol, y_resol)},
      end{end}
{
    fullscreen();

    exit_button = new Graph_lib::Button({x_resol - yes_no_bs, 0}, yes_no_bs, yes_no_bs, "Quit", cb_end);
    new_button = new Graph_lib::Button({x_resol - yes_no_bs, yes_no_bs}, yes_no_bs, yes_no_bs, "New game", cb_exit);

    mode_ch = new modeChoose(*this, cb_start);

    play_ag = new playAgain(*this, cb_exit, cb_end);

    color(Graph_lib::Color::white);

    mode_ch = new modeChoose(*this, cb_start);

    attach(*mode_ch);

    while (!started and Fl::wait())
    {
    }

    calc_field_params(this);

    mode_ch->hide();

    attach(*exit_button);
    attach(*new_button);

    Fl::redraw();
}

void myWin::start(Graph_lib::Address addr)
{
    Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(addr);

    int j = (w.x() + choose_mode_bs * 3 / 2 - x_max() / 2) / choose_mode_bs;
    int i = (w.y() + choose_mode_bs - y_max() / 2) / choose_mode_bs;

    int mode = i * 3 + j;

    width = modes[mode].first;
    height = modes[mode].second;

    started = true;
}
