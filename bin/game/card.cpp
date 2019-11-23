#include "card.h"

using namespace Graph_lib;

Card::Card(int x, int y, std::string img_name, Graph_lib::Callback cb_show)
    : img{Point{x * (cr_sz_x + shft), y * (cr_sz_y + shft)}, img_name},
      show{Point{x * (cr_sz_x + shft), y * (cr_sz_y + shft)}, cr_sz_x, cr_sz_y, "", cb_show},
      Rectangle{Point{x * (cr_sz_x + shft), y * (cr_sz_y + shft)}, cr_sz_x, cr_sz_y},
      x{x},
      y{y}
{
    Rectangle::set_fill_color(Graph_lib::Color::dark_blue);
}

void Card::click()
{
    is_clicked = !is_clicked;
}

void Card::attach(Graph_lib::Window &win)
{
    win.attach(show);
}

void Card::draw_lines() const
{
    if (is_clicked)
    {
        Rectangle::draw();
    }
    else
    {
        img.draw();
    }
}
