#include "card.h"

using namespace Graph_lib;

Card::Card(int x, int y, std::string img_name)
    : Image{Point{x * (cr_sz_x + shft), y * (cr_sz_y + shft)}, source + img_name},
      Button{Point{x * (cr_sz_x + shft), y * (cr_sz_y + shft)}, cr_sz_x, cr_sz_y, "", cb_show},
      Rectangle{
          Point{x * (cr_sz_x + shft), y * (cr_sz_y + shft)},
          cr_sz_x,
          cr_sz_y,
      }
{
}

void Card::cb_show(Address, Address addr)
{
    Graph_lib::reference_to<Card>(addr).click();
}

void Card::click()
{
    is_clicked = !is_clicked;
    Fl::redraw();
}

void Card::attach(Graph_lib::Window &win)
{
    Button::attach(win);
}

void Card::draw_lines() const
{
    if (is_clicked)
    {
        Rectangle::draw_lines();
    }
    else
    {
        Image::draw_lines();
    }
}
