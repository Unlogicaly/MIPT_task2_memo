#include "field.h"
#include <algorithm>
#include <chrono>
#include <random>

Card *Field::get_card(int x, int y)
{
    return cards[(x - side_gap) / (cr_sz_x + shft)][(y - up_gap) / (cr_sz_y + shft)];
}

std::vector<int> get_pairs()
{
    srand(time(NULL));
    std::vector<int> res(height * width);
    for (auto i = 0; i < res.size(); ++i)
    {
        res[i] = i;
    }
    std::random_shuffle(res.begin(), res.end());

    return res;
}

Field::Field() : Simple_window({0, 0}, 1920, 1080, "")
{

    for (auto i = 0; i < height; ++i)
    {
        cards.emplace_back();
        for (auto j = 0; j < width; ++j)
        {
            cards[i].push_back(new Card(i, j, get_pic("apple", cr_sz_x), cb_show));
            attach(*cards[i][j]);
            attach(cards[i][j]->show);
        }
    }
}

void Field::flip(Graph_lib::Address pwin)
{
    Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(pwin);
    auto c = get_card(w.x(), w.y());
    c->click();
    Fl::redraw();
}
