#include "field.h"
#include <algorithm>
#include <chrono>
#include <random>

Card *Field::get_card(int x, int y)
{
    return cards[(x - side_gap) / (cr_sz_x + shft)][(y - up_gap) / (cr_sz_y + shft)];
}

std::vector<int> rand_range()
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

Field::Field() : Simple_window({0, 0}, 1920, 1080, ""), opened{nullptr}
{
    std::vector<std::string> pictures;
    get_names(pictures);
    std::random_shuffle(pictures.begin(), pictures.end());

    std::vector<int> pairs = rand_range();

    for (auto i = 0; i < height; ++i)
    {
        cards.emplace_back();
        for (auto j = 0; j < width; ++j)
            cards[i].push_back(nullptr);
    }

    for (auto i = 0; i < height * width; i += 2)
    {
        int i1 = pairs[i] / width, j1 = pairs[i] % width;
        cards[i1][j1] = new Card(i1, j1, get_pic(pictures[i / 2], cr_sz_x), cb_show);
        attach(*cards[i1][j1]);
        attach(cards[i1][j1]->show);

        int i2 = pairs[i + 1] / width, j2 = pairs[i + 1] % width;
        cards[i2][j2] = new Card(i2, j2, get_pic(pictures[i / 2], cr_sz_x), cb_show);
        attach(*cards[i2][j2]);
        attach(cards[i2][j2]->show);
    }
}

void Field::flip(Graph_lib::Address pwin)
{
    Fl_Widget &w = Graph_lib::reference_to<Fl_Widget>(pwin);
    auto c = get_card(w.x(), w.y());
    c->click();
    Fl::redraw();
}
