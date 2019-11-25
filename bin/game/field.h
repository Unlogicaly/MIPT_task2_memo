#ifndef FIELD_H
#define FIELD_H

#include "card.h"
#include "editting_files.h"

std::vector<int> get_pairs();

std::vector<int> rand_range(int max);

class Field : public Simple_window
{
  private:
    static void cb_show(Graph_lib::Address pwin, Graph_lib::Address pwid)
    {
        Graph_lib::reference_to<Field>(pwid).flip(pwin);
    }

    std::vector<std::vector<Card *>> cards;

    std::pair<Card *, Card *> opened;

    int ready = 0;

    int height, width, size, shift, side_gap, up_gap;

    point get_point(int x, int y) { return {side_gap + (size + shift) * x, up_gap + (size + shift) * y}; }

    void treat_last(Card *treat_last);

    Graph_lib::Out_box messages;

    void exit();

  public:
    Field(int height, int width, int size, int shift, int side_gap, int up_gap);

    Card *get_card(int x, int y);

    void flip(Graph_lib::Address pwin);
};

#endif // FIELD_H
