#ifndef FIELD_H
#define FIELD_H

#include "card.h"
#include "pictures_treatment.h"

class Field : public Simple_window
{
  private:
    static void cb_show(Graph_lib::Address pwin, Graph_lib::Address pwid)
    {
        Graph_lib::reference_to<Field>(pwid).flip(pwin);
    }

    std::vector<std::vector<Card *>> cards;

  public:
    Field();

    Card *get_card(int x, int y);

    void flip(Graph_lib::Address pwin);
};

#endif // FIELD_H
