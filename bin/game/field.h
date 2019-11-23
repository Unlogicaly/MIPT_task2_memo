#ifndef FIELD_H
#define FIELD_H

#include "card.h"
#include "editting_files.h"

std::vector<int> get_pairs();

#define ull unsigned long long

template <typename T>
std::vector<T> matrix_1d(ull length, T fill = 0)
{
    std::vector<T> res(length);
    for (ull i = 0; i < length; ++i)
        res[i] = fill;
    return res;
}

template <typename T>
std::vector<std::vector<T>> matrix_2d(ull height, ull width, T fill = 0)
{
    std::vector<std::vector<T>> res(height, matrix_1d(width, fill));
    return res;
}

std::vector<int> rand_range();

class Field : public Simple_window
{
  private:
    static void cb_show(Graph_lib::Address pwin, Graph_lib::Address pwid)
    {
        Graph_lib::reference_to<Field>(pwid).flip(pwin);
    }

    std::vector<std::vector<Card *>> cards;

    Card *opened;

  public:
    Field();

    Card *get_card(int x, int y);

    void flip(Graph_lib::Address pwin);
};

#endif // FIELD_H
