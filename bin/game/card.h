#ifndef CARD_H
#define CARD_H
#include "create_window.h"

class Card : public Graph_lib::Image, public Graph_lib::Button, public Graph_lib::Rectangle
{
  private:
    // uniq number in card matrix: x & y
    int x;
    int y;

    bool is_clicked = false;

  public:
    Card(int x, int y, std::string img_name = "default");
    static void cb_show(Graph_lib::Address, Graph_lib::Address addr);
    void click();

    void attach(Graph_lib::Window &) override;
    void draw_lines() const override;
};

#endif // CARD_H
