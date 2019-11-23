#ifndef CARD_H
#define CARD_H
#include "create_window.h"

class Card : public Graph_lib::Rectangle
{
  private:
    // uniq number in card matrix: x & y
    int x;
    int y;

    Graph_lib::Image img;

    bool is_clicked = false;

  public:
    Graph_lib::Button show;

    Card(int x, int y, std::string img_name, Graph_lib::Callback cb_show);

    void click();

    void attach(Graph_lib::Window &win);
    void draw_lines() const override;
};

#endif // CARD_H
