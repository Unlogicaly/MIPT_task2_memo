#include "mywin.h"

playAgain::playAgain(myWin &win, Graph_lib::Callback cb_again, Graph_lib::Callback cb_end)
    : Widget::Widget({0, 0}, 0, 0, "", [](Graph_lib::Address, Graph_lib::Address) {}),
      asc{nullptr},
      yes_b{nullptr},
      yes_im{nullptr},
      no_b{nullptr},
      no_im{nullptr},
      back{nullptr},
      _size{win.get_choose_mode_bs()},
      win{win}

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

void playAgain::attach(Graph_lib::Window &win)
{
    win.attach(*back);

    win.attach(*asc);

    win.attach(*yes_b);
    win.attach(*yes_im);

    win.attach(*no_b);
    win.attach(*no_im);
}

void playAgain::hide_q()
{
    win.detach(*asc);

    win.detach(*back);

    no_b->hide();
    win.detach(*no_im);

    yes_b->hide();
    win.detach(*yes_im);
}

void playAgain::show_q()
{
    win.attach(*asc);

    win.attach(*back);

    yes_b->show();
    win.attach(*yes_im);

    no_b->show();
    win.attach(*no_im);
}

playAgain::~playAgain()
{
    delete asc;
    delete no_im;
    delete no_b;
    delete yes_im;
    delete yes_b;
}
