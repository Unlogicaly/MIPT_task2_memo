#include "card.h"

using namespace Graph_lib;

Card::Card(int x, int y, point p, int size, std::string img_name, Graph_lib::Callback cb_show)
    : Rectangle{Point{p.first, p.second}, size, size},
      x{x},
      y{y},
      img{Point{p.first, p.second}, img_name},
      frame{Point{p.first, p.second}, get_pic("frame", size, size)},
      size{size},
      name{img_name},
      show{new Graph_lib::Button(Point{p.first, p.second}, size, size, "", cb_show)}
{
    Rectangle::set_fill_color(Graph_lib::Color::dark_blue);
}

void Card::click()
{
    is_clicked = !is_clicked;
}

void Card::attach(Graph_lib::Window &win)
{
    win.attach(*show);
}

void Card::draw_lines() const
{
    if (is_clicked)
    {
        img.draw();
        if (is_found)
        {
            frame.draw();
        }
    }
    else
    {
        Rectangle::draw_lines();
    }
}

Card::~Card()
{
    delete show;
}
