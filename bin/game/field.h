#ifndef FIELD_H
#define FIELD_H

#include "card.h"
#include "editting_files.h"

std::vector<int> get_pairs();

std::vector<int> rand_range(int max, int seed = -1);

class Field : public myWin
{
  private:
    static void cb_show(Graph_lib::Address pwin, Graph_lib::Address pwid)
    {
        Graph_lib::reference_to<Field>(pwid).flip(pwin);
    }

    std::vector<std::vector<Card *>> cards;

    std::pair<Card *, Card *> opened;

    int ready = 0;

    int size, shift, side_gap, up_gap;

    point get_point(int x, int y) { return {side_gap + (size + shift) * x, up_gap + (size + shift) * y}; }

    void treat_last(Card *treat_last);

    Graph_lib::Out_box messages;

  public:
    Field(bool &end, int size, int shift, int side_gap, int up_gap);

    Card *get_card(int x, int y);

    void flip(Graph_lib::Address pwin);

    void hide_field()
    {
        for (auto &line : cards)
            for (auto card : line)
            {
                delete card;
            }
    }

    ~Field();
};

#endif // FIELD_H
