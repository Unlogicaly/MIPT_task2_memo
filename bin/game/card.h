#ifndef CARD_H
#define CARD_H

#include "mywin.h"

#define point std::pair<int, int>

class Card : public Graph_lib::Rectangle
{
  private:
    // uniq number in card matrix: x & y
    int x;
    int y;

    Graph_lib::Image img;

    bool is_clicked = false;

    int size;

    std::string name;

  public:
    Graph_lib::Button *show;

    Card(int x, int y, point p, int size, std::string img_name, Graph_lib::Callback cb_show);

    void click();

    void attach(Graph_lib::Window &win);
    void draw_lines() const override;

    std::string get_name() { return name; }
};

#endif // CARD_H
