#include "grid.h"

Grid::Grid(int x_size, int y_size, int x_tick, int y_tick, Graph_lib::Color::Color_type c,
           Graph_lib::Line_style::Line_style_type style, int width)
{

    grid.set_color(c);
    grid.set_style(Graph_lib::Line_style{style, width});

    for (auto x = x_tick; x < x_size; x += x_tick)
        grid.add(Graph_lib::Point{x, 0}, Graph_lib::Point{x, y_size});

    for (auto y = y_tick; y < y_size; y += y_tick)
        grid.add(Graph_lib::Point{0, y}, Graph_lib::Point{x_size, y});
}

void Grid::draw_lines() const
{
    grid.draw_lines();
}
