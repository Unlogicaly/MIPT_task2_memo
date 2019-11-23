#ifndef CREATE_WINDOW_H
#define CREATE_WINDOW_H

#include "grid.h"

Simple_window *create_window(const std::string &size = "max", bool with_grid = false, const Graph_lib::Point p = {0, 0},
                             const std::string &title = "", Fl_Color c = Graph_lib::Color::white);

#endif // CREATE_WINDOW_H
