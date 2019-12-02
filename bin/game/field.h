#ifndef FIELD_H
#define FIELD_H

#include "card.h"

#define ull unsigned long long

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

    point get_point(int x, int y) const
    {
        return {get_side_gap() + (get_size() + get_shift()) * x, get_up_gap() + (get_size() + get_shift()) * y};
    }

    void treat_last(Card *treat_last);

  public:
    Field(bool &end, int x_resol, int y_resol);

    Card *get_card(int x, int y);

    void flip(Graph_lib::Address pwin);

    ~Field();
};

#endif // FIELD_H
