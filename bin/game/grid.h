#ifndef GRID_H
#define GRID_H

#include "..\\..\\Graph_lib\\Graph.h"
#include "..\\..\\Graph_lib\\Simple_window.h"

class Grid : public Graph_lib::Lines
{
  private:
    Graph_lib::Lines grid;

  public:
    Grid(int x_size, int y_size, int x_tick, int y_tick, Graph_lib::Color::Color_type c = Graph_lib::Color::black,
         Graph_lib::Line_style::Line_style_type style = Graph_lib::Line_style::dot, int width = 1);

  protected:
    void draw_lines() const override;
};

#endif // GRID_H
