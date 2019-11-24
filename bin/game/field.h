#ifndef FIELD_H
#define FIELD_H

#include "card.h"
#include "editting_files.h"

std::vector<int> get_pairs();

std::vector<int> rand_range();

class Field : public Simple_window
{
  private:
    static void cb_show(Graph_lib::Address pwin, Graph_lib::Address pwid)
    {
        Graph_lib::reference_to<Field>(pwid).flip(pwin);
    }

    std::vector<std::vector<Card *>> cards;

    std::pair<Card *, Card *> opened;

  public:
    Field();

    Card *get_card(int x, int y);

    void flip(Graph_lib::Address pwin);
};

#endif // FIELD_H
