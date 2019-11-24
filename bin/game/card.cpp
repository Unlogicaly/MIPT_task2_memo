#include "card.h"

using namespace Graph_lib;

Card::Card(int x, int y, std::string img_name, Graph_lib::Callback cb_show)
    : img{Point{side_gap + x * (cr_sz_x + shft), up_gap + y * (cr_sz_y + shft)}, img_name},
      show{new Graph_lib::Button(Point{side_gap + x * (cr_sz_x + shft), up_gap + y * (cr_sz_y + shft)}, cr_sz_x,
                                 cr_sz_y, "", cb_show)},
      Rectangle{Point{side_gap + x * (cr_sz_x + shft), up_gap + y * (cr_sz_y + shft)}, cr_sz_x, cr_sz_y},
      x{x},
      y{y},
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
