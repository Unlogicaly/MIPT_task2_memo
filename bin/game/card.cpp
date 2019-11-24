#include "card.h"

using namespace Graph_lib;

Card::Card(int x, int y, point p, int size, std::string img_name, Graph_lib::Callback cb_show)
    : img{Point{p.first, p.second}, img_name},
      show{new Graph_lib::Button(Point{p.first, p.second}, size, size, "", cb_show)},
      Rectangle{Point{p.first, p.second}, size, size},
      x{x},
      y{y},
      size{size},
      name{img_name}
{
    Rectangle::set_fill_color(Graph_lib::Color::dark_blue);
}

void Card::click()
{
    is_clicked = !is_clicked;
    draw_lines();
}

void Card::attach(Graph_lib::Window &win)
{
    win.attach(*show);
    show->attach(win);
}

void Card::draw_lines() const
{
    if (is_clicked)
    {
        img.draw();
    }
    else
    {
        Rectangle::draw_lines();
    }
}
